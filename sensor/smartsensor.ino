//r divider VCC ***** 75k ***** 32 ***** 10k ***** GND

#include <BLEDevice.h>
#include <EEPROM.h>
#include <LoRa.h>
#include <SPI.h>

//define SX1278
#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)

//define EEPROM
#define EEPROM_SIZE 64
#define FIRST_ADDRESS 0
#define SENSOR_ROUND_DURATION_SET_ADDRESS 8

#define BAND    433E6  //frequency 433Mhz
#define BATTERYPIN 32  //battery checker pin
#define SLEEP_DURATION 1 * 60
#define EMERGENCY_HIBERNATE 1 * 60
#define RETRY 3

char* FLORA_DEVICES[] = {
  "C1:AC:6E:32:E7:0D"
};

TaskHandle_t hibernateTaskHandle = NULL;
static int deviceCount = sizeof FLORA_DEVICES / sizeof FLORA_DEVICES[0];  //lora array
static BLEUUID serviceUUID("00001204-0000-1000-8000-00805f9b34fb");
static BLEUUID uuid_version_battery("00001a02-0000-1000-8000-00805f9b34fb");
static BLEUUID uuid_sensor_data("00001a01-0000-1000-8000-00805f9b34fb");
static BLEUUID uuid_write_mode("00001a00-0000-1000-8000-00805f9b34fb");

float temperatureData, batteryData;
int moistureData, fertilityData, lightData, firstState, sensorRoundSet;
uint32_t sendMillis;

String outgoing;              // outgoing message
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xA8;     // address of this device
byte destination = 0xA9;      // destination to send to

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("ESP32 LORA FLORA SENSOR");
  EEPROM.begin(EEPROM_SIZE);

  readConfig();  //restore config
  readBattery();  //read battery voltage
  readFlora();  //request mi flower data
  initLora();  //start lora chip
  delay(500);
  sendData();  //send data to master
}

void loop() {

  if (millis() - sendMillis > 6000) {
    sendData();
  }

  onReceive(LoRa.parsePacket());  //wait 30 sec incoming command
  if (millis() > 30000) hibernate();

}

void readConfig() {
  firstState = EEPROM.read(FIRST_ADDRESS);
  Serial.print("First State : "); Serial.println(firstState);

  if (firstState == 5) {
    sensorRoundSet = EEPROM.read(SENSOR_ROUND_DURATION_SET_ADDRESS);
    Serial.print("restore sensor round set : "); Serial.println(sensorRoundSet);
  } else {
    EEPROM.write(FIRST_ADDRESS, 5);
    EEPROM.write(SENSOR_ROUND_DURATION_SET_ADDRESS, 15);
    EEPROM.commit();
    Serial.println("write config first");
  }
}

void readBattery() {
  for (int i = 0; i < 5; i++) {
    batteryData += analogRead(BATTERYPIN);
    delay(500);
  }

  batteryData = batteryData / 5;
  batteryData = (batteryData * 37.9 / 4095);

  Serial.print("battery : "); Serial.println(batteryData);
}

void hibernate() {
  LoRa.end();
  LoRa.sleep();
  if ((sensorRoundSet < 1) || (sensorRoundSet > 99)) sensorRoundSet = 15;
  Serial.print("Going to sleep "); Serial.print(sensorRoundSet); Serial.println(" min");
  esp_sleep_enable_timer_wakeup((sensorRoundSet * SLEEP_DURATION) * 1000000ll);
  delay(100);
  esp_deep_sleep_start();
}

void delayedHibernate(void *parameter) {
  delay(EMERGENCY_HIBERNATE * 1000); // delay for 1 minutes
  Serial.println("Something got stuck, entering emergency hibernate...");
  hibernate();
}
