#define BLYNK_PRINT Serial
#include "time.h"
#include <BlynkSimpleEsp32.h>
#include <Adafruit_ILI9341.h>
//#include <FirebaseESP32.h>
#include <Adafruit_GFX.h>
//#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WidgetRTC.h>
#include <EEPROM.h>
#include <SPI.h>
#include <BLEDevice.h>
#include "config.h"
#include "helper.h"

int modeSelect;   //1:Manual  2:Auto  3:Timer
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

char Date[16];
char Time[16];
char lastupdateWheather[16];

float temperatureData, batteryData;
int moistureData, fertilityData, lightData;  //Not use
int pressureData, humidityData, windspeedData;

int manual_Switch, auto_Switch, oldModeButtonState;

int tesmod, reading, firstState, lightSetWrite, lastMode,
    timerNumber, CurrentWifiSignal, WifiSignal, firstDisplay, msgCount, 
    timer1Work, timer2Work,timer3Work, timer4Work, timer5Work, timer6Work, timer7Work, timer8Work, 
    mqttConnectCount, connectCount;

bool sensorStatus;
bool rainStatus, rainDelayWork, lastRainDelay;
bool buttonActive, longPressActive, dots, firstLoop, firstRecieve, mqttUpdate;

bool zone1ValveStatus, zone2ValveStatus, zone3ValveStatus, zone4ValveStatus;
bool zone1AutoTimerWork, zone2AutoTimerWork, zone3AutoTimerWork, zone4AutoTimerWork;
bool zone1AutoTimerStatus, zone2AutoTimerStatus, zone3AutoTimerStatus, zone4AutoTimerStatus;
bool lastZone1ValveStatus, lastZone2ValveStatus, lastZone3ValveStatus, lastZone4ValveStatus;
bool lastZone1, lastZone2, lastZone3, lastZone4;
bool lastAutoZone1, lastAutoZone2, lastAutoZone3, lastAutoZone4;

bool timer1Zone1Status, timer1Zone2Status, timer1Zone3Status, timer1Zone4Status;
bool timer2Zone1Status, timer2Zone2Status, timer2Zone3Status, timer2Zone4Status;
bool timer3Zone1Status, timer3Zone2Status, timer3Zone3Status, timer3Zone4Status;
bool timer4Zone1Status, timer4Zone2Status, timer4Zone3Status, timer4Zone4Status;
bool timer5Zone1Status, timer5Zone2Status, timer5Zone3Status, timer5Zone4Status;
bool timer6Zone1Status, timer6Zone2Status, timer6Zone3Status, timer6Zone4Status;
bool timer7Zone1Status, timer7Zone2Status, timer7Zone3Status, timer7Zone4Status;
bool timer8Zone1Status, timer8Zone2Status, timer8Zone3Status, timer8Zone4Status;
bool timer1On, timer2On, timer3On, timer4On, timer5On, timer6On, timer7On, timer8On;

uint32_t startsecondswd, stopsecondswd, nowseconds, buttonTimer, autoMillis, currentMillis,
         newMillis, sensorRoundMillis, mqttMillis, runTime;

String  weatherMain, weatherDescription, weatherCity, outgoing, incoming;

String display_dayofweek, display_monthofyear, display_dayofmonth, display_year,
       display_hour, display_minutes, display_seconds;

BlynkTimer timer;
WidgetRTC rtc;

WidgetTerminal terminal(Widget_TerminalBug);
WidgetLED zone1BlynkLed(Widget_Zone1Led);
WidgetLED zone2BlynkLed(Widget_Zone2Led);
WidgetLED zone3BlynkLed(Widget_Zone3Led);
WidgetLED zone4BlynkLed(Widget_Zone4Led);
WidgetLED rainStatusBlynkLed(Widget_RainStatusLed);

//**************************************************************************************************//
//*********************************************SETUP************************************************//

void setup() {
  pinMode(manualSwitch, INPUT_PULLUP);
  pinMode(autoSwitch, INPUT_PULLUP);
  pinMode(zone1Valve, OUTPUT); digitalWrite(zone1Valve, HIGH);
  pinMode(zone2Valve, OUTPUT); digitalWrite(zone2Valve, HIGH);
  pinMode(zone3Valve, OUTPUT); digitalWrite(zone2Valve, HIGH);
  pinMode(zone4Valve, OUTPUT); digitalWrite(zone2Valve, HIGH);

#ifdef PHYBUTTON
  pinMode(zone1Button, INPUT_PULLUP);
  pinMode(zone2Button, INPUT_PULLUP);
  pinMode(zone3Button, INPUT_PULLUP);
  pinMode(zone4Button, INPUT_PULLUP);

#endif

  Serial.begin(115200);
  while (!Serial);
  Serial.println("");

  EEPROM.begin(EEPROM_SIZE);
  forceStopAllValve();
  readConfig();
  connectInternet();

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getTime();
  
  updateWeather();

  rtc.begin();
  //timer.setInterval(5000L, reconnectBlynk);  //30000
  timer.setInterval(10000L, activeToday);
  timer.setInterval(10000L, writeEeprom);
  timer.setInterval(10000L, updateBlynk);
#ifdef ILI9341
  timer.setInterval(10000L, displayWifi);
#endif
#ifdef WEATHER
  timer.setInterval(86400000L, updateWeather);
#endif

  //FreeRTOS
  xTaskCreate(&wifiConnectTask, "wifiConnect", 3000, NULL, 10, NULL);
  xTaskCreate(&blynkConnectTask, "blynkConnect", 3000, NULL, 10, NULL);
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
  modeButtonCheck();
  if ( modeSelect == 1 ) {
    manualButtonCheck();  //Only Maunal mode allow to control button
  }
#endif

#ifdef ILI9341
  checkDisplayButtonSet();
  displayClock();
#endif

}

void checkValve() {

  //zone1 valve check
  if (zone1ValveStatus == 1) {
    digitalWrite(zone1Valve, LOW);
    zone1BlynkLed.on();
  } else {
    digitalWrite(zone1Valve, HIGH);
    zone1BlynkLed.off();
  }

  //zone2 valve check
  if (zone2ValveStatus == 1) {
    digitalWrite(zone2Valve, LOW);
    zone2BlynkLed.on();
  } else {
    digitalWrite(zone2Valve, HIGH);
    zone2BlynkLed.off();
  }

  //zone3 valve check
  if (zone3ValveStatus == 1) {
    digitalWrite(zone3Valve, LOW);
    zone3BlynkLed.on();
  } else {
    digitalWrite(zone3Valve, HIGH);
    zone3BlynkLed.off();
  }

  //zone4 valve check
  if (zone4ValveStatus == 1) {
    digitalWrite(zone4Valve, LOW);
    zone4BlynkLed.on();
  } else {
    digitalWrite(zone4Valve, HIGH);
    zone4BlynkLed.off();
  }


}

void closeAllValve() {  //for close all valve
  if ((zone1ValveStatus  == 1) || (zone2ValveStatus == 1)
      || (zone3ValveStatus  == 1) || (zone4ValveStatus == 1)) {
    zone1ValveStatus = 0;
    zone2ValveStatus = 0;
    zone3ValveStatus = 0;
    zone4ValveStatus = 0;
  }
}

void openAllValve() {  //for close all valve
  if ((zone1ValveStatus  == 0) || (zone2ValveStatus == 0)
      || (zone3ValveStatus  == 0) || (zone4ValveStatus == 0)) {
    zone1ValveStatus = 1;
    zone2ValveStatus = 1;
    zone3ValveStatus = 1;
    zone4ValveStatus = 1;
  }
}

void activeToday() {
  if (year() != 1970) {
    if (modeSelect == 3) {
      //0=off 1=zone1 2=zone2 3=zone3 4=zone4 5=all zone
      if ((timer1Work == 1) || (timer1Work == 2) || (timer1Work == 3) || (timer1Work == 4) || (timer1Work == 5)) {
        Blynk.syncVirtual(Widget_TimerInput_1);
      } else if (timer1Work == 0) {
        timer1CloseAll();
        timer1On = 0;
      }

      if ((timer2Work == 1) || (timer2Work == 2) || (timer2Work == 3) || (timer2Work == 4) || (timer2Work == 5)) {
        Blynk.syncVirtual(Widget_TimerInput_2);
      } else if (timer2Work == 0) {
        timer2CloseAll();
        timer2On = 0;
      }

      if ((timer3Work == 1) || (timer3Work == 2) || (timer3Work == 3) || (timer3Work == 4) || (timer3Work == 5)) {
        Blynk.syncVirtual(Widget_TimerInput_3);
      } else if (timer3Work == 0) {
        timer3CloseAll();
        timer3On = 0;
      }

      if ((timer4Work == 1) || (timer4Work == 2) || (timer4Work == 3 || (timer4Work == 4) || (timer4Work == 5))) {
        Blynk.syncVirtual(Widget_TimerInput_4);
      } else if (timer4Work == 0) {
        timer4CloseAll();
        timer4On = 0;
      }

      if ((timer5Work == 1) || (timer5Work == 2) || (timer5Work == 3) || (timer5Work == 4) || (timer5Work == 5)) {
        Blynk.syncVirtual(Widget_TimerInput_5);
      } else if (timer5Work == 0) {
        timer5CloseAll();
        timer5On = 0;
      }

      if ((timer6Work == 1) || (timer6Work == 2) || (timer6Work == 3) || (timer6Work == 4) || (timer6Work == 5)) {
        Blynk.syncVirtual(Widget_TimerInput_6);
      } else if (timer6Work == 0) {
        timer6CloseAll();
        timer6On = 0;
      }

      if ((timer7Work == 1) || (timer7Work == 2) || (timer7Work == 3) || (timer7Work == 4) || (timer7Work == 5)) {
        Blynk.syncVirtual(Widget_TimerInput_7);
      } else if (timer7Work == 0) {
        timer7CloseAll();
        timer7On = 0;
      }

      if ((timer8Work == 1) || (timer8Work == 2) || (timer8Work == 3) || (timer8Work == 4) || (timer8Work == 5)) {
        Blynk.syncVirtual(Widget_TimerInput_8);
      } else if (timer8Work == 0) {
        timer8CloseAll();
        timer8On = 0;
      }

    } else if (modeSelect == 2) {

      if (zone1AutoTimerWork == 1) Blynk.syncVirtual(Widget_Zone1AutoTimerInput);
      if (zone2AutoTimerWork == 1) Blynk.syncVirtual(Widget_Zone2AutoTimerInput);
      if (zone3AutoTimerWork == 1) Blynk.syncVirtual(Widget_Zone3AutoTimerInput);
      if (zone4AutoTimerWork == 1) Blynk.syncVirtual(Widget_Zone4AutoTimerInput);
    }
  }

}

//  end code //
