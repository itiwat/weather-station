//******************************************************************************************//
//******************************************OTHER FUNCTION**********************************//

void getTime() {

  //https://lastminuteengineers.com/esp32-ntp-server-date-time-tutorial/
  //https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  /*
    %A  returns day of week
    %B  returns month of year
    %d  returns day of month
    %Y  returns year
    %H  returns hour
    %M  returns minutes
    %S  returns seconds
  */

  String xoxo = (timeinfo, "%A, %B %d %Y %H:%M:%S");
//  displayYear = String(&timeinfo, "%Y");
//  displayMonth = String(&timeinfo, "%B");
//  displayDayOfMonth = String(&timeinfo, "%d");
  Serial.print("xo : ");Serial.println(xoxo);

  /*xoxo  displayYear =   String(year(), DEC);
    displayYear =   displayYear.substring(2, 4);

    int gmMonth = month();
    displayMonth =   String(gmMonth, DEC);
    int monthdigits = displayMonth.length();
    if (monthdigits == 1) displayMonth = "0" + displayMonth;

    int gmDayOfMonth = day();
    displayDayOfMonth =   String(gmDayOfMonth, DEC);
    int daydigits = displayDayOfMonth.length();
    if (daydigits == 1) displayDayOfMonth = "0" + displayDayOfMonth;

    int gmthour = hour();
    if (gmthour == 24) gmthour = 0;
    displayHour =   String(gmthour, DEC);
    int hourdigits = displayHour.length();
    if (hourdigits == 1) displayHour = "0" + displayHour;

    displayMinute = String(minute(), DEC);
    int minutedigits = displayMinute.length();
    if (minutedigits == 1) displayMinute = "0" + displayMinute;
    oxox*/

#ifdef ILI9341

  tft.setCursor(70, 47);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(1);
  //tft.print(Day[weekday()]);
  //tft.print(getLocalTime(&timeinfo, "%A"));
  tft.print(" ");
  tft.print(displayDayOfMonth);
  tft.print("/");
  tft.print(displayMonth);
  tft.print("/");
  tft.print(displayYear);

#endif

}

void writeEeprom() {
  int modeSelectTmp = EEPROM.read(MODE_SELECT_ADDRESS);
  int sensorRoundSetTmp = EEPROM.read(SENSOR_ROUND_DURATION_SET_ADDRESS);
  int temperatureSetTmp = EEPROM.read(TEMPERATURE_SET_ADDRESS);
  int moistureSetTmp = EEPROM.read(MOISTURE_SET_ADDRESS);
  int lightSetTmp = EEPROM.read(LIGHT_SET_ADDRESS);
  int timer1WorkTmp = EEPROM.read(TIMER1_ADDRESS);
  int timer2WorkTmp = EEPROM.read(TIMER2_ADDRESS);
  int timer3WorkTmp = EEPROM.read(TIMER3_ADDRESS);
  int timer4WorkTmp = EEPROM.read(TIMER4_ADDRESS);
  int timer5WorkTmp = EEPROM.read(TIMER5_ADDRESS);
  int timer6WorkTmp = EEPROM.read(TIMER6_ADDRESS);
  int timer7WorkTmp = EEPROM.read(TIMER7_ADDRESS);
  int timer8WorkTmp = EEPROM.read(TIMER8_ADDRESS);
  int autoWaterSprayDurationSetTmp = EEPROM.read(AUTO_WATER_SPRAY_DURATION_SET_ADDRESS);
  bool zone1AutoTimerWorkTmp = EEPROM.read(ZONE1_AUTO_TIMER_ADDRESS);
  bool zone2AutoTimerWorkTmp = EEPROM.read(ZONE2_AUTO_TIMER_ADDRESS);
  bool zone3AutoTimerWorkTmp = EEPROM.read(ZONE3_AUTO_TIMER_ADDRESS);
  bool zone4AutoTimerWorkTmp = EEPROM.read(ZONE4_AUTO_TIMER_ADDRESS);
  bool rainDelayWorkTmp = EEPROM.read(RAIN_DELAY_ADDRESS);

  if (modeSelect != modeSelectTmp) {
    EEPROM.write(MODE_SELECT_ADDRESS, modeSelect);
    Serial.print("write eeprom mode select : "); Serial.println(modeSelect);
  }

  if (sensorRoundSet != sensorRoundSetTmp) {
    EEPROM.write(SENSOR_ROUND_DURATION_SET_ADDRESS, sensorRoundSet);
    Serial.print("eeprom write sensor round set : "); Serial.println(sensorRoundSet);
  }

  if (temperatureSet != temperatureSetTmp) {
    EEPROM.write(TEMPERATURE_SET_ADDRESS, temperatureSet);
    Serial.print("eeprom write temerature set : "); Serial.println(temperatureSet);
  }

  if (moistureSet != moistureSetTmp) {
    EEPROM.write(MOISTURE_SET_ADDRESS, moistureSet);
    Serial.print("eeprom write moisture set : "); Serial.println(moistureSet);
  }

  lightSetWrite = lightSet / 1000;
  if (lightSetWrite != lightSetTmp) {
    if (lightSetWrite <= 0) lightSetWrite = 0;
    if (lightSetWrite >= 99) lightSetWrite = 99;
    EEPROM.write(LIGHT_SET_ADDRESS, lightSetWrite);
    Serial.print("eeprom write light set : "); Serial.println(lightSetWrite);
  }

  if (autoWaterSprayDurationSet != autoWaterSprayDurationSetTmp) {
    EEPROM.write(AUTO_WATER_SPRAY_DURATION_SET_ADDRESS, autoWaterSprayDurationSet);
    Serial.print("eeprom write water time set : "); Serial.println(autoWaterSprayDurationSet);
  }

  if (zone1AutoTimerWork != zone1AutoTimerWorkTmp) {
    EEPROM.write(ZONE1_AUTO_TIMER_ADDRESS, zone1AutoTimerWork);
    Serial.print("eeprom write auto zone1 timerwork : "); Serial.println(zone1AutoTimerWork);
  }

  if (zone2AutoTimerWork != zone2AutoTimerWorkTmp) {
    EEPROM.write(ZONE2_AUTO_TIMER_ADDRESS, zone2AutoTimerWork);
    Serial.print("eeprom write auto zone2 timer work : "); Serial.println(zone2AutoTimerWork);
  }

  if (zone3AutoTimerWork != zone3AutoTimerWorkTmp) {
    EEPROM.write(ZONE3_AUTO_TIMER_ADDRESS, zone3AutoTimerWork);
    Serial.print("eeprom write auto zone3 timerwork : "); Serial.println(zone3AutoTimerWork);
  }

  if (zone4AutoTimerWork != zone4AutoTimerWorkTmp) {
    EEPROM.write(ZONE4_AUTO_TIMER_ADDRESS, zone4AutoTimerWork);
    Serial.print("eeprom write auto zone4 timerwork : "); Serial.println(zone4AutoTimerWork);
  }

  if (rainDelayWork != rainDelayWorkTmp) {
    EEPROM.write(RAIN_DELAY_ADDRESS, rainDelayWork);
    Serial.print("eeprom write rain delay : "); Serial.println(rainDelayWork);
  }

  if (timer1Work != timer1WorkTmp) {
    EEPROM.write(TIMER1_ADDRESS, timer1Work);
    Serial.print("eeprom write Timer 1 Work : "); Serial.println(timer1Work);
  }

  if (timer2Work != timer2WorkTmp) {
    EEPROM.write(TIMER2_ADDRESS, timer2Work);
    Serial.print("eeprom write Timer 2 Work : "); Serial.println(timer2Work);
  }

  if (timer3Work != timer3WorkTmp) {
    EEPROM.write(TIMER3_ADDRESS, timer3Work);
    Serial.print("eeprom write Timer 3 Work : "); Serial.println(timer3Work);
  }

  if (timer4Work != timer4WorkTmp) {
    EEPROM.write(TIMER4_ADDRESS, timer4Work);
    Serial.print("eeprom write Timer 4 Work : "); Serial.println(timer4Work);
  }

  if (timer5Work != timer5WorkTmp) {
    EEPROM.write(TIMER5_ADDRESS, timer5Work);
    Serial.print("eeprom write Timer 5 Work : "); Serial.println(timer5Work);
  }

  if (timer6Work != timer6WorkTmp) {
    EEPROM.write(TIMER6_ADDRESS, timer6Work);
    Serial.print("eeprom write Timer 6 Work : "); Serial.println(timer6Work);
  }

  if (timer7Work != timer7WorkTmp) {
    EEPROM.write(TIMER7_ADDRESS, timer7Work);
    Serial.print("eeprom write Timer 7 Work : "); Serial.println(timer7Work);
  }

  if (timer8Work != timer8WorkTmp) {
    EEPROM.write(TIMER8_ADDRESS, timer8Work);
    Serial.print("eeprom write Timer 8 Work : "); Serial.println(timer8Work);
  }

  EEPROM.commit();
}


void readConfig() {

  firstState = EEPROM.read(FIRST_ADDRESS);

  if (firstState == 5) {
    modeSelect = EEPROM.read(MODE_SELECT_ADDRESS);
    sensorRoundSet = EEPROM.read(SENSOR_ROUND_DURATION_SET_ADDRESS);
    temperatureSet = EEPROM.read(TEMPERATURE_SET_ADDRESS);
    moistureSet = EEPROM.read(MOISTURE_SET_ADDRESS);
    lightSetWrite = EEPROM.read(LIGHT_SET_ADDRESS) ;
    autoWaterSprayDurationSet = EEPROM.read(AUTO_WATER_SPRAY_DURATION_SET_ADDRESS);
    zone1AutoTimerWork = EEPROM.read(ZONE1_AUTO_TIMER_ADDRESS);
    zone2AutoTimerWork = EEPROM.read(ZONE2_AUTO_TIMER_ADDRESS);
    zone3AutoTimerWork = EEPROM.read(ZONE3_AUTO_TIMER_ADDRESS);
    zone4AutoTimerWork = EEPROM.read(ZONE4_AUTO_TIMER_ADDRESS);
    rainDelayWork = EEPROM.read(RAIN_DELAY_ADDRESS);
    timer1Work = EEPROM.read(TIMER1_ADDRESS);
    timer2Work = EEPROM.read(TIMER2_ADDRESS);
    timer3Work = EEPROM.read(TIMER3_ADDRESS);
    timer4Work = EEPROM.read(TIMER4_ADDRESS);
    timer5Work = EEPROM.read(TIMER5_ADDRESS);
    timer6Work = EEPROM.read(TIMER6_ADDRESS);
    timer7Work = EEPROM.read(TIMER7_ADDRESS);
    timer8Work = EEPROM.read(TIMER8_ADDRESS);
    Serial.println("restore config");
  } else {
    EEPROM.write(FIRST_ADDRESS, 5);
    EEPROM.write(MODE_SELECT_ADDRESS, 1);
    EEPROM.write(SENSOR_ROUND_DURATION_SET_ADDRESS, 15);
    EEPROM.write(TEMPERATURE_SET_ADDRESS, 32);
    EEPROM.write(MOISTURE_SET_ADDRESS, 50);
    EEPROM.write(LIGHT_SET_ADDRESS, 20);
    EEPROM.write(AUTO_WATER_SPRAY_DURATION_SET_ADDRESS, 1);
    EEPROM.write(ZONE1_AUTO_TIMER_ADDRESS, 1);
    EEPROM.write(ZONE2_AUTO_TIMER_ADDRESS, 1);
    EEPROM.write(ZONE3_AUTO_TIMER_ADDRESS, 1);
    EEPROM.write(ZONE4_AUTO_TIMER_ADDRESS, 1);
    EEPROM.write(AUTO_WATER_SPRAY_DURATION_SET_ADDRESS, 1);
    EEPROM.write(RAIN_DELAY_ADDRESS, 0);
    EEPROM.write(TIMER1_ADDRESS, 0);
    EEPROM.write(TIMER2_ADDRESS, 0);
    EEPROM.write(TIMER3_ADDRESS, 0);
    EEPROM.write(TIMER4_ADDRESS, 0);
    EEPROM.write(TIMER5_ADDRESS, 0);
    EEPROM.write(TIMER6_ADDRESS, 0);
    EEPROM.write(TIMER7_ADDRESS, 0);
    EEPROM.write(TIMER8_ADDRESS, 0);
    EEPROM.commit();
    Serial.println("write config first");
  }
}

void forceStopAllTimer() {
  timer1CloseAll();
  timer2CloseAll();
  timer3CloseAll();
  timer4CloseAll();
  timer5CloseAll();
  timer6CloseAll();
  timer7CloseAll();
  timer8CloseAll();

  Blynk.syncVirtual(Widget_TimerInput_1, 0);
  Blynk.syncVirtual(Widget_TimerInput_2, 0);
  Blynk.syncVirtual(Widget_TimerInput_3, 0);
  Blynk.syncVirtual(Widget_TimerInput_4, 0);
  Blynk.syncVirtual(Widget_TimerInput_5, 0);
  Blynk.syncVirtual(Widget_TimerInput_6, 0);
  Blynk.syncVirtual(Widget_TimerInput_7, 0);
  Blynk.syncVirtual(Widget_TimerInput_8, 0);
}

void forceStopAllValve() {
  zone1ValveStatus = 0;
  zone2ValveStatus = 0;
  zone3ValveStatus = 0;
  zone4ValveStatus = 0;
}

void resetSensor() {
  rainStatus = 0;
  sensorStatus = 0;
  sensorRoundStatus = 0;
}

//**************************************************************************************************//
//**************************************PHYSICAL BUTTON*********************************************//

#ifdef PHYBUTTON
void modeButtonCheck() {
  int Mode;

  if (digitalRead(manualSwitch) == LOW ) {
    Mode = 1;
  }
  else if (digitalRead(autoSwitch) == LOW ) {
    Mode = 2;
  }
  else {
    Mode = 3;
  }

  // It have change Mode
  if ( Mode != oldModeButtonState) {
    delay(10);
    forceStopAllTimer();
    closeAllValve();
    resetTerminal();
    modeSelect = Mode;
    modeLabel();
    if ( Mode == 1 ) {
      Serial.println("Change mode to : Manual");
    }
    else if ( Mode == 2 ) {
      Serial.println("Change mode to : Auto");
    }
    else if ( Mode == 3 ) {
      Serial.println("Change mode to : Timer");
    }
  }
  oldModeButtonState = Mode;
  /*xoxo  if ((dataModeButton == 0) && (oldModeButtonState == 1)) {
      delay(10);
      if (digitalRead(modeButton) == 0) {
        forceStopAllTimer();
        closeAllValve();
        resetTerminal();
        modeSelect++;
        if (modeSelect >= 4) modeSelect = 1;
        modeLabel();
        Serial.println("mode button");
      }
    }
    oldModeButtonState = dataModeButton;
    oxox*/
}

void manualButtonCheck() {
  if ((digitalRead(zone1Button) == LOW) || (digitalRead(zone2Button) == LOW)
      || (digitalRead(zone3Button) == LOW) || (digitalRead(zone4Button) == LOW)) {

    Serial.print("zone1Button : ");
    Serial.println(digitalRead(zone1Button));
    Serial.print("zone2Button : ");
    Serial.println(digitalRead(zone2Button));
    Serial.print("zone3Button : ");
    Serial.println(digitalRead(zone3Button));
    Serial.print("zone4Button : ");
    Serial.println(digitalRead(zone4Button));

    if (buttonActive == 0) {
      buttonActive = 1;
      buttonTimer = millis();
    }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == 0)) {
      longPressActive = 1;  //Hold Button do nothings
      return;
    }
    else {
      if (buttonActive == 1) {
        if (longPressActive == 1) {
          longPressActive = 0;
        }
        else if (digitalRead(zone1Button) == LOW) {
          forceStopAllTimer();
          resetTerminal();
          if (zone1ValveStatus == 1) {
            modeSelect = 1;
            zone1ValveStatus = 0;

            modeLabel();
          } else {
            modeSelect = 1;

            zone1ValveStatus = 1;
            modeLabel();
          }
          Serial.println("Activate : zone1");
        }
        else if (digitalRead(zone2Button) == LOW) {
          forceStopAllTimer();
          resetTerminal();
          if (zone2ValveStatus == 1) {
            modeSelect = 1;
            zone2ValveStatus = 0;

            modeLabel();
          } else {
            modeSelect = 1;

            zone2ValveStatus = 1;
            modeLabel();
          }
          Serial.println("Activate : zone2");
        }
        else if (digitalRead(zone3Button) == LOW) {
          forceStopAllTimer();
          resetTerminal();
          if (zone3ValveStatus == 1) {
            modeSelect = 1;
            zone3ValveStatus = 0;

            modeLabel();
          } else {
            modeSelect = 1;

            zone3ValveStatus = 1;
            modeLabel();
          }
          Serial.println("Activate : zone3");
        }
        else if (digitalRead(zone4Button) == LOW) {
          forceStopAllTimer();
          resetTerminal();
          if (zone4ValveStatus == 1) {
            modeSelect = 1;
            zone4ValveStatus = 0;

            modeLabel();
          } else {
            modeSelect = 1;

            zone4ValveStatus = 1;
            modeLabel();
          }
          Serial.println("Activate : zone4");
        }
      }
    }
    buttonActive = 0;
  }
}
#endif

/*xoxo
  void manualButtonCheck() {
  if (digitalRead(manualButton) == LOW) {
    if (buttonActive == 0) {
      buttonActive = 1;
      buttonTimer = millis();
    }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == 0)) {
      longPressActive = 1;
      forceStopAllTimer();
      resetTerminal();
      if (zone2ValveStatus == 1) {
        modeSelect = 1;
        zone2ValveStatus = 0;

        modeLabel();
      } else {
        modeSelect = 1;

        zone2ValveStatus = 1;
        modeLabel();
      }
      Serial.println("zone2");
    }
  } else {
    if (buttonActive == 1) {
      if (longPressActive == 1) {
        longPressActive = 0;
      } else {

        forceStopAllTimer();
        resetTerminal();
        if (zone1ValveStatus == 1) {
          modeSelect = 1;
          zone1ValveStatus = 0;

          modeLabel();
        } else {
          modeSelect = 1;

          zone1ValveStatus = 1;
          modeLabel();
        }
        Serial.println("zone1");
      }
      buttonActive = 0;
    }
  }
  }
  #endif oxox*/
