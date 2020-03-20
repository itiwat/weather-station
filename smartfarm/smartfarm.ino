#define BLYNK_PRINT Serial
#include <TridentTD_LineNotify.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_ILI9341.h>
#include <FirebaseESP32.h>
#include <Adafruit_GFX.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WidgetRTC.h>
#include <EEPROM.h>
#include <LoRa.h>
#include <SPI.h>
#include "config.h"
#include "helper.h"

int modeSelect = 1;
int sensorRoundSet = 15;
int temperatureSet = 32;
int moistureSet = 80;
int lightSet = 20;
int autoWaterSprayDurationSet = 1;
bool isFirstConnect = 1;
bool sensorRoundStatus = 1;
uint32_t longPressTime = 500;
String timeStamp = "wait";
String todaySchedule = "wait";
String baseTopic = "espcalendar/";

char *Day[] = {" ", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
char Date[16];
char Time[16];

float temperatureData, batteryData;

int moistureData, fertilityData, lightData, tesmod, reading, firstState, lightSetWrite, lastMode,
    timerNumber, CurrentWifiSignal, WifiSignal, firstDisplay, msgCount, timer1Work, timer2Work,
    timer3Work, timer4Work, timer5Work, timer6Work, timer7Work, timer8Work, mqttConnectCount, 
    connectCount;

bool waterValveStatus, sprayValveStatus, waterAutoTimerWork, sprayAutoTimerWork, waterAutoTimerStatus,
     sprayAutoTimerStatus, rainStatus, sensorStatus, rainDelayWork, lastWaterValveStatus, lastSprayValveStatus;

bool buttonActive, longPressActive, oldModeButtonState, dataModeButton, dots, lastWater, lastSpray,
     lastAutoWater, lastAutoSpray, lastRainDelay, firstLoop, firstRecieve, mqttUpdate;

bool timer1WaterStatus, timer1SprayStatus, timer2WaterStatus, timer2SprayStatus, timer3WaterStatus,
     timer3SprayStatus, timer4WaterStatus, timer4SprayStatus, timer5WaterStatus, timer5SprayStatus,
     timer6WaterStatus, timer6SprayStatus, timer7WaterStatus, timer7SprayStatus, timer8WaterStatus,
     timer8SprayStatus, timer1On, timer2On, timer3On, timer4On, timer5On, timer6On, timer7On, 
     timer8On;

uint32_t startsecondswd, stopsecondswd, nowseconds, buttonTimer, autoMillis, currentMillis,
         newMillis, sensorRoundMillis, mqttMillis, runTime;

String  weatherMain, weatherDescription, weatherCity, displayTime, displayHour, displayMinute,
        lineNotifyMessage, lineSender, lineMessage, lineDataSet, displayDayOfMonth, displayMonth,
        displayYear, outgoing, incoming;

BlynkTimer timer;
WidgetRTC rtc;

WidgetTerminal terminal(Widget_TerminalBug);
WidgetLED waterBlynkLed(Widget_WaterLed);
WidgetLED sprayBlynkLed(Widget_SprayLed);
WidgetLED rainBlynkLed(Widget_RainDelayLed);

#ifdef CALENDAR
WiFiClient espClient;
PubSubClient client(espClient);
#endif
#ifdef FIREBASE
FirebaseData firebaseData;
#endif

//**************************************************************************************************//
//*********************************************SETUP************************************************//

void setup() {
  pinMode(waterValve, OUTPUT); digitalWrite(waterValve, HIGH);
  pinMode(sprayValve, OUTPUT); digitalWrite(sprayValve, HIGH);
  pinMode(valve3, OUTPUT); digitalWrite(valve3, HIGH);
  pinMode(valve4, OUTPUT); digitalWrite(valve4, HIGH);
  pinMode(waterLed, OUTPUT); digitalWrite(waterLed, LOW);
  pinMode(sprayLed, OUTPUT); digitalWrite(sprayLed, LOW);

#ifdef PHYBUTTON
  pinMode(manualButton, INPUT_PULLUP);
  pinMode(modeButton, INPUT_PULLUP);
#endif
#ifdef LINENOTIFY
  Serial.println(LINE.getVersion());
  LINE.setToken(LINE_TOKEN);
#endif

  Serial.begin(115200);
  while (!Serial);
  Serial.println("");

  EEPROM.begin(EEPROM_SIZE);
  forceStopAllValve();
  readConfig();
  connectInternet();

  rtc.begin();
  //timer.setInterval(5000L, reconnectBlynk);  //30000
  timer.setInterval(10000L, activeToday);
  timer.setInterval(10000L, writeEeprom);
  timer.setInterval(10000L, updateBlynk);

#ifdef ILI9341
  timer.setInterval(10000L, displayWifi);
#endif

  initLora();

//FreeRTOS
  xTaskCreate(&blynkConnectTask, "blynkConnect", 3000, NULL, 10, NULL);
  xTaskCreate(&wifiConnectTask, "wifiConnect", 3000, NULL, 10, NULL);

#ifdef CALENDAR
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
#endif
}

//**************************************************************************************************//
//************************************************ LOOP ********************************************//

void loop() {
  currentMillis = millis();
  checkValve();
  checkFunction();

  if (Blynk.connected()) {
    Blynk.run();
  }

  timer.run();
  onReceive(LoRa.parsePacket());
  checkDefine();
  checkDebug();
}

//**************************************************************************************************//
//*******************************************CHECK FUNCTION*****************************************//

void checkDebug() {
  newMillis = millis();
  if ((newMillis - currentMillis) < 10 ) Serial.println(newMillis - currentMillis);
  //Serial.println(newMillis - currentMillis);
}

void checkFunction() {

  if (modeSelect == 2) {
    autoCheck();
  } else if (modeSelect == 3) {
    timerCheck();
  }

  if (((currentMillis - sensorRoundMillis) >= ((sensorRoundSet * ONE_MINUTE) + 30000)) && (sensorRoundStatus == 0)) {
    sensorRoundStatus = 1;
  }

  if (firstLoop == 0) {

#ifdef ILI9341
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(BLACK);
    drawUi();
    displayDataSensor();
    displayButtonSet();
    displayDataSet();
#endif

    getTime();
    resetTerminal();
    firstLoop = 1;
  }
}

void checkDefine() {
#ifdef PHYBUTTON
  manualButtonCheck();
  modeButtonCheck();
#endif

#ifdef ILI9341
  checkDisplayButtonSet();
  displayClock();
#endif

#ifdef CALENDAR
  if (mqttUpdate == 0) {
    mqttConnect();
  }

  if (((currentMillis - mqttMillis) > 300000) && (mqttUpdate == 1)) {
    mqttUpdate = 0;
  }

  client.loop();
#endif

}

void checkValve() {

  //water valve check
  if (waterValveStatus == 1) {
    digitalWrite(waterValve, LOW);
    waterBlynkLed.on();
  } else {
    digitalWrite(waterValve, HIGH);
    waterBlynkLed.off();
  }

  //spray valve check
  if (sprayValveStatus == 1) {
    digitalWrite(sprayValve, LOW);
    sprayBlynkLed.on();
  } else {
    digitalWrite(sprayValve, HIGH);
    sprayBlynkLed.off();
  }

}

void closeAllValve() {  //for close all valve
  if ((waterValveStatus  == 1) || (sprayValveStatus == 1)) {
    waterValveStatus = 0;
    sprayValveStatus = 0;

#ifdef LINENOTIFY
    lineNotifyCloseAllValve();
#endif

  }
}

void openAllValve() {  //for close all valve
  if ((waterValveStatus  == 0) || (sprayValveStatus == 0)) {
    waterValveStatus = 1;
    sprayValveStatus = 1;

#ifdef LINENOTIFY
    lineNotifyOpenAllValve();
#endif

  }
}

void activeToday() {
  if (year() != 1970) {
    if (modeSelect == 3) {

      if ((timer1Work == 1) || (timer1Work == 2) || (timer1Work == 3)) {
        Blynk.syncVirtual(Widget_TimerInput_1);
      } else if (timer1Work == 0) {
        timer1CloseAll();
        timer1On = 0;
      }

      if ((timer2Work == 1) || (timer2Work == 2) || (timer2Work == 3)) {
        Blynk.syncVirtual(Widget_TimerInput_2);
      } else if (timer2Work == 0) {
        timer2CloseAll();
        timer2On = 0;
      }

      if ((timer3Work == 1) || (timer3Work == 2) || (timer3Work == 3)) {
        Blynk.syncVirtual(Widget_TimerInput_3);
      } else if (timer3Work == 0) {
        timer3CloseAll();
        timer3On = 0;
      }

      if ((timer4Work == 1) || (timer4Work == 2) || (timer4Work == 3)) {
        Blynk.syncVirtual(Widget_TimerInput_4);
      } else if (timer4Work == 0) {
        timer4CloseAll();
        timer4On = 0;
      }

      if ((timer5Work == 1) || (timer5Work == 2) || (timer5Work == 3)) {
        Blynk.syncVirtual(Widget_TimerInput_5);
      } else if (timer5Work == 0) {
        timer5CloseAll();
        timer5On = 0;
      }

      if ((timer6Work == 1) || (timer6Work == 2) || (timer6Work == 3)) {
        Blynk.syncVirtual(Widget_TimerInput_6);
      } else if (timer6Work == 0) {
        timer6CloseAll();
        timer6On = 0;
      }

      if ((timer7Work == 1) || (timer7Work == 2) || (timer7Work == 3)) {
        Blynk.syncVirtual(Widget_TimerInput_7);
      } else if (timer7Work == 0) {
        timer7CloseAll();
        timer7On = 0;
      }

      if ((timer8Work == 1) || (timer8Work == 2) || (timer8Work == 3)) {
        Blynk.syncVirtual(Widget_TimerInput_8);
      } else if (timer8Work == 0) {
        timer8CloseAll();
        timer8On = 0;
      }

    } else if (modeSelect == 2) {

      if (waterAutoTimerWork == 1) Blynk.syncVirtual(Widget_WaterAutoTimerInput);
      if (sprayAutoTimerWork == 1) Blynk.syncVirtual(Widget_SprayAutoTimerInput);
    }
  }

}

//  end code //
