//******************************************************************************************//
//******************************************OTHER FUNCTION**********************************//

void getTime() {

  displayYear =   String(year(), DEC);
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

#ifdef ILI9341

  tft.setCursor(70, 47);
  tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(1);
  tft.print(Day[weekday()]);
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
  bool waterAutoTimerWorkTmp = EEPROM.read(WATER_AUTO_TIMER_ADDRESS);
  bool sprayAutoTimerWorkTmp = EEPROM.read(SPRAY_AUTO_TIMER_ADDRESS);
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

  if (waterAutoTimerWork != waterAutoTimerWorkTmp) {
    EEPROM.write(WATER_AUTO_TIMER_ADDRESS, waterAutoTimerWork);
    Serial.print("eeprom write auto water timerwork : "); Serial.println(waterAutoTimerWork);
  }

  if (sprayAutoTimerWork != sprayAutoTimerWorkTmp) {
    EEPROM.write(SPRAY_AUTO_TIMER_ADDRESS, sprayAutoTimerWork);
    Serial.print("eeprom write auto spray timer work : "); Serial.println(sprayAutoTimerWork);
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
    waterAutoTimerWork = EEPROM.read(WATER_AUTO_TIMER_ADDRESS);
    sprayAutoTimerWork = EEPROM.read(SPRAY_AUTO_TIMER_ADDRESS);
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
    EEPROM.write(WATER_AUTO_TIMER_ADDRESS, 1);
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
  waterValveStatus = 0;
  sprayValveStatus = 0;
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
  dataModeButton = digitalRead(modeButton);
  if ((dataModeButton == 0) && (oldModeButtonState == 1)) {
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
}

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
      if (sprayValveStatus == 1) {
        modeSelect = 1;
        sprayValveStatus = 0;
        lineSender = "Manual User";

#ifdef LINENOTIFY
        lineNotifyCloseSprayValve();
#endif

        modeLabel();
      } else {
        modeSelect = 1;
        lineSender = "Manual User";

#ifdef LINENOTIFY
        lineNotifyOpenSprayValve();
#endif

        sprayValveStatus = 1;
        modeLabel();
      }
      Serial.println("spray");
    }
  } else {
    if (buttonActive == 1) {
      if (longPressActive == 1) {
        longPressActive = 0;
      } else {

        forceStopAllTimer();
        resetTerminal();
        if (waterValveStatus == 1) {
          modeSelect = 1;
          waterValveStatus = 0;
          lineSender = "Manual User";

#ifdef LINENOTIFY
          lineNotifyCloseWaterValve();
#endif

          modeLabel();
        } else {
          modeSelect = 1;
          lineSender = "Manual User";

#ifdef LINENOTIFY
          lineNotifyOpenWaterValve();
#endif

          waterValveStatus = 1;
          modeLabel();
        }
        Serial.println("water");
      }
      buttonActive = 0;
    }
  }
}
#endif
