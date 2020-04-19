//******************************************************************************************//
//******************************************BLYNK*****************************************//

BLYNK_WRITE(Widget_SensorRoundSetSlide) {  //Sensor Round Set
  sensorRoundSet = param[0].asInt();

#ifdef ILI9341
  displayDataSet();
  Serial.println("sensor round set");
#endif

}

BLYNK_WRITE(Widget_TemperatureSetSlide) {  //temperature set
  temperatureSet = param[0].asInt();

#ifdef ILI9341
  displayDataSet();
  Serial.println("temperature set");
#endif

}

BLYNK_WRITE(Widget_MoistureSetSlide) {  //moisture set
  moistureSet = param[0].asInt();

#ifdef ILI9341
  displayDataSet();
  Serial.println("moisture set");
#endif

}

BLYNK_WRITE(Widget_LightSetSlide) {  //light set
  lightSet = map(param.asInt(), 0, 99, 0, 99999);
  Blynk.virtualWrite(Widget_LightLabel, lightSet);
  //Blynk.setProperty(Widget_LightSetSlide, "label", lightSet);

#ifdef ILI9341
  displayDataSet();
  Serial.println("light set");
#endif

}

BLYNK_WRITE(Widget_WaterSprayDurationSetSlide) {  //water time duration set
  autoWaterSprayDurationSet = param[0].asInt();

#ifdef ILI9341
  displayDataSet();
  Serial.println("zone3 time duration set");
#endif

}

BLYNK_WRITE(Widget_Zone1Button) {  //zone1 manual button
  if ( modeSelect != 1 ) {
    return;  //If not in manual mode ignore control from app
  }
  forceStopAllTimer();
  resetTerminal();
  if (param.asInt() == 1) {
    modeSelect = 1;

    zone1ValveStatus = 1;
    modeLabel();
  } else {
    modeSelect = 1;
    zone1ValveStatus = 0;

    modeLabel();
  }
}

BLYNK_WRITE(Widget_Zone2Button) {  //zone2 manual button
  if ( modeSelect != 1 ) {
    return;  //If not in manual mode ignore control from app
  }
  forceStopAllTimer();
  resetTerminal();
  if (param.asInt() == 1) {
    modeSelect = 1;

    zone2ValveStatus = 1;
    modeLabel();
  } else {
    modeSelect = 1;
    zone2ValveStatus = 0;

    modeLabel();
  }
}

BLYNK_WRITE(Widget_Zone3Button) {  //zone3 manual button
  if ( modeSelect != 1 ) {
    return;  //If not in manual mode ignore control from app
  }
  forceStopAllTimer();
  resetTerminal();
  if (param.asInt() == 1) {
    modeSelect = 1;

    zone3ValveStatus = 1;
    modeLabel();
  } else {
    modeSelect = 1;
    zone3ValveStatus = 0;

    modeLabel();
  }
}

BLYNK_WRITE(Widget_Zone4Button) {  //zone4 manual button
  if ( modeSelect != 1 ) {
    return;  //If not in manual mode ignore control from app
  }
  forceStopAllTimer();
  resetTerminal();
  if (param.asInt() == 1) {
    modeSelect = 1;

    zone4ValveStatus = 1;
    modeLabel();
  } else {
    modeSelect = 1;
    zone4ValveStatus = 0;

    modeLabel();
  }
}

BLYNK_WRITE(Widget_Zone1AutoTimerButton) {  //zone1 work button
  if (param.asInt() == 1) {
    zone1AutoTimerWork = 1;
  } else {
    zone1AutoTimerWork = 0;
  }
}

BLYNK_WRITE(Widget_Zone2AutoTimerButton) {  //zone2 work button
  if (param.asInt() == 1) {
    zone2AutoTimerWork = 1;
  } else {
    zone2AutoTimerWork = 0;
  }
}

BLYNK_WRITE(Widget_Zone3AutoTimerButton) {  //zone3 work button
  if (param.asInt() == 1) {
    zone3AutoTimerWork = 1;
  } else {
    zone3AutoTimerWork = 0;
  }
}

BLYNK_WRITE(Widget_Zone4AutoTimerButton) {  //zone4 work button
  if (param.asInt() == 1) {
    zone4AutoTimerWork = 1;
  } else {
    zone4AutoTimerWork = 0;
  }
}

void updateBlynk() {
  /*
  Blynk.virtualWrite(V1, temperatureData);
  Blynk.virtualWrite(V2, moistureData);
  Blynk.virtualWrite(V3, fertilityData);
  Blynk.virtualWrite(V4, lightData);
  */
  Blynk.virtualWrite(V1, temperatureData);
  Blynk.virtualWrite(V2, humidityData);
  Blynk.virtualWrite(V3, pressureData);
  Blynk.virtualWrite(V4, windspeedData);
}

void syncAllBlynk() {
  modeSelect = EEPROM.read(MODE_SELECT_ADDRESS);
  sensorRoundSet = EEPROM.read(SENSOR_ROUND_DURATION_SET_ADDRESS);
  temperatureSet = EEPROM.read(TEMPERATURE_SET_ADDRESS);
  moistureSet = EEPROM.read(MOISTURE_SET_ADDRESS);
  lightSetWrite = EEPROM.read(LIGHT_SET_ADDRESS);
  lightSet = lightSetWrite * 1000;
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

  modeLabel();
  timer1Label();
  timer2Label();
  timer3Label();
  timer4Label();
  timer5Label();
  timer6Label();
  timer7Label();
  timer8Label();

  Blynk.virtualWrite(Widget_Zone1AutoTimerButton, zone1AutoTimerWork);
  Blynk.virtualWrite(Widget_Zone2AutoTimerButton, zone2AutoTimerWork);
  Blynk.virtualWrite(Widget_Zone3AutoTimerButton, zone3AutoTimerWork);
  Blynk.virtualWrite(Widget_Zone4AutoTimerButton, zone4AutoTimerWork);
  Blynk.virtualWrite(Widget_SensorRoundSetSlide, sensorRoundSet);
  Blynk.virtualWrite(Widget_MoistureSetSlide, moistureSet);
  Blynk.virtualWrite(Widget_WaterSprayDurationSetSlide, autoWaterSprayDurationSet);
  Blynk.virtualWrite(Widget_RainDelayButton, rainDelayWork);
  Blynk.virtualWrite(Widget_TemperatureSetSlide, temperatureSet);
  Blynk.virtualWrite(Widget_LightSetSlide, lightSetWrite);
  Blynk.virtualWrite(Widget_LightLabel, lightSet);
}

void resetTerminal() {
  terminal.println(); terminal.println(); terminal.println(); terminal.println(); terminal.println();
  terminal.println(); terminal.println(); terminal.println(); terminal.println(); terminal.println();
  terminal.println(); terminal.println(); terminal.println(); terminal.println(); terminal.println();
  terminal.println(); terminal.println(); terminal.println(); terminal.println(); terminal.println();
  terminal.println(); terminal.println(); terminal.println(); terminal.println(); terminal.println();
  terminal.println(); terminal.println(); terminal.println(); terminal.println(); terminal.println();
  terminal.println(); terminal.println(); terminal.println(); terminal.println(); terminal.println();
  terminal.println(); terminal.println(); terminal.println(); terminal.println(); terminal.println();
  terminal.flush();
}

void modeLabel() {
  if (modeSelect == 1) {
    Blynk.virtualWrite(Widget_ModeDisplay, "MANUAL");
    Blynk.virtualWrite(Widget_ManualControlDisplay, "Push Button");
  }
  else if (modeSelect == 2) {
    Blynk.virtualWrite(Widget_ModeDisplay, "AUTO");
    Blynk.virtualWrite(Widget_ManualControlDisplay, "Button not response if not within manual mode");
  }
  else if (modeSelect == 3) {
    Blynk.virtualWrite(Widget_ModeDisplay, "TIMER");
    Blynk.virtualWrite(Widget_ManualControlDisplay, "Button not response if not within manual mode");
  }

  Blynk.virtualWrite(Widget_Zone1Button, zone1ValveStatus);
  Blynk.virtualWrite(Widget_Zone2Button, zone2ValveStatus);
  Blynk.virtualWrite(Widget_Zone3Button, zone3ValveStatus);
  Blynk.virtualWrite(Widget_Zone4Button, zone4ValveStatus);

}

void timer1Label() {
  if (timer1Work == 0) {
    Blynk.setProperty(Widget_TimerButton_1, "onLabel", "OFF");
    Blynk.setProperty(Widget_TimerButton_1, "offLabel", "OFF");
    Blynk.setProperty(Widget_TimerInput_1, "label", "TIMER 1 (OFF)");
  } else if (timer1Work == 1) {
    Blynk.setProperty(Widget_TimerButton_1, "onLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerButton_1, "offLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerInput_1, "label", "TIMER 1 (ZONE1)");

  } else if (timer1Work == 2) {
    Blynk.setProperty(Widget_TimerButton_1, "onLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerButton_1, "offLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerInput_1, "label", "TIMER 1 (ZONE2)");

  } else if (timer1Work == 3) {
    Blynk.setProperty(Widget_TimerButton_1, "onLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerButton_1, "offLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerInput_1, "label", "TIMER 1 (ZONE3)");
  }
    else if (timer1Work == 4) {
    Blynk.setProperty(Widget_TimerButton_1, "onLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerButton_1, "offLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerInput_1, "label", "TIMER 1 (ZONE4)");
  }
  else if (timer1Work == 5) {
    Blynk.setProperty(Widget_TimerButton_1, "onLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerButton_1, "offLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerInput_1, "label", "TIMER 1 (ALL ZONE)");
  }
}

void timer2Label() {
  if (timer2Work == 0) {
    Blynk.setProperty(Widget_TimerButton_2, "onLabel", "OFF");
    Blynk.setProperty(Widget_TimerButton_2, "offLabel", "OFF");
    Blynk.setProperty(Widget_TimerInput_2, "label", "TIMER 2 (OFF)");
  } else if (timer2Work == 1) {
    Blynk.setProperty(Widget_TimerButton_2, "onLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerButton_2, "offLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerInput_2, "label", "TIMER 2 (ZONE1)");

  } else if (timer2Work == 2) {
    Blynk.setProperty(Widget_TimerButton_2, "onLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerButton_2, "offLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerInput_2, "label", "TIMER 2 (ZONE2)");

  } else if (timer2Work == 3) {
    Blynk.setProperty(Widget_TimerButton_2, "onLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerButton_2, "offLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerInput_2, "label", "TIMER 2 (ZONE3)");
  }
    else if (timer2Work == 4) {
    Blynk.setProperty(Widget_TimerButton_2, "onLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerButton_2, "offLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerInput_2, "label", "TIMER 2 (ZONE4)");
  }
  else if (timer2Work == 5) {
    Blynk.setProperty(Widget_TimerButton_2, "onLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerButton_2, "offLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerInput_2, "label", "TIMER 2 (ALL ZONE)");
  }
}

void timer3Label() {
  if (timer3Work == 0) {
    Blynk.setProperty(Widget_TimerButton_3, "onLabel", "OFF");
    Blynk.setProperty(Widget_TimerButton_3, "offLabel", "OFF");
    Blynk.setProperty(Widget_TimerInput_3, "label", "TIMER 3 (OFF)");
  } else if (timer3Work == 1) {
    Blynk.setProperty(Widget_TimerButton_3, "onLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerButton_3, "offLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerInput_3, "label", "TIMER 3 (ZONE1)");

  } else if (timer3Work == 2) {
    Blynk.setProperty(Widget_TimerButton_3, "onLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerButton_3, "offLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerInput_3, "label", "TIMER 3 (ZONE2)");

  } else if (timer3Work == 3) {
    Blynk.setProperty(Widget_TimerButton_3, "onLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerButton_3, "offLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerInput_3, "label", "TIMER 3 (ZONE3)");
  }
    else if (timer3Work == 4) {
    Blynk.setProperty(Widget_TimerButton_3, "onLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerButton_3, "offLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerInput_3, "label", "TIMER 3 (ZONE4)");
  }
  else if (timer3Work == 5) {
    Blynk.setProperty(Widget_TimerButton_3, "onLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerButton_3, "offLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerInput_3, "label", "TIMER 3 (ALL ZONE)");
  }
}

void timer4Label() {
  if (timer4Work == 0) {
    Blynk.setProperty(Widget_TimerButton_4, "onLabel", "OFF");
    Blynk.setProperty(Widget_TimerButton_4, "offLabel", "OFF");
    Blynk.setProperty(Widget_TimerInput_4, "label", "TIMER 4 (OFF)");
  } else if (timer4Work == 1) {
    Blynk.setProperty(Widget_TimerButton_4, "onLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerButton_4, "offLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerInput_4, "label", "TIMER 4 (ZONE1)");

  } else if (timer4Work == 2) {
    Blynk.setProperty(Widget_TimerButton_4, "onLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerButton_4, "offLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerInput_4, "label", "TIMER 4 (ZONE2)");

  } else if (timer4Work == 3) {
    Blynk.setProperty(Widget_TimerButton_4, "onLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerButton_4, "offLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerInput_4, "label", "TIMER 4 (ZONE3)");
  }
    else if (timer4Work == 4) {
    Blynk.setProperty(Widget_TimerButton_4, "onLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerButton_4, "offLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerInput_4, "label", "TIMER 4 (ZONE4)");
  }
  else if (timer4Work == 5) {
    Blynk.setProperty(Widget_TimerButton_4, "onLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerButton_4, "offLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerInput_4, "label", "TIMER 4 (ALL ZONE)");
  }
}

void timer5Label() {
  if (timer5Work == 0) {
    Blynk.setProperty(Widget_TimerButton_5, "onLabel", "OFF");
    Blynk.setProperty(Widget_TimerButton_5, "offLabel", "OFF");
    Blynk.setProperty(Widget_TimerInput_5, "label", "TIMER 5 (OFF)");
  } else if (timer5Work == 1) {
    Blynk.setProperty(Widget_TimerButton_5, "onLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerButton_5, "offLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerInput_5, "label", "TIMER 5 (ZONE1)");

  } else if (timer5Work == 2) {
    Blynk.setProperty(Widget_TimerButton_5, "onLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerButton_5, "offLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerInput_5, "label", "TIMER 5 (ZONE2)");

  } else if (timer5Work == 3) {
    Blynk.setProperty(Widget_TimerButton_5, "onLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerButton_5, "offLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerInput_5, "label", "TIMER 5 (ZONE3)");
  }
    else if (timer5Work == 4) {
    Blynk.setProperty(Widget_TimerButton_5, "onLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerButton_5, "offLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerInput_5, "label", "TIMER 5 (ZONE4)");
  }
  else if (timer5Work == 5) {
    Blynk.setProperty(Widget_TimerButton_5, "onLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerButton_5, "offLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerInput_5, "label", "TIMER 5 (ALL ZONE)");
  }
}

void timer6Label() {
  if (timer6Work == 0) {
    Blynk.setProperty(Widget_TimerButton_6, "onLabel", "OFF");
    Blynk.setProperty(Widget_TimerButton_6, "offLabel", "OFF");
    Blynk.setProperty(Widget_TimerInput_6, "label", "TIMER 6 (OFF)");
  } else if (timer6Work == 1) {
    Blynk.setProperty(Widget_TimerButton_6, "onLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerButton_6, "offLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerInput_6, "label", "TIMER 6 (ZONE1)");

  } else if (timer6Work == 2) {
    Blynk.setProperty(Widget_TimerButton_6, "onLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerButton_6, "offLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerInput_6, "label", "TIMER 6 (ZONE2)");

  } else if (timer6Work == 3) {
    Blynk.setProperty(Widget_TimerButton_6, "onLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerButton_6, "offLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerInput_6, "label", "TIMER 6 (ZONE3)");
  }
    else if (timer6Work == 4) {
    Blynk.setProperty(Widget_TimerButton_6, "onLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerButton_6, "offLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerInput_6, "label", "TIMER 6 (ZONE4)");
  }
  else if (timer6Work == 5) {
    Blynk.setProperty(Widget_TimerButton_6, "onLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerButton_6, "offLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerInput_6, "label", "TIMER 6 (ALL ZONE)");
  }
}

void timer7Label() {
  if (timer7Work == 0) {
    Blynk.setProperty(Widget_TimerButton_7, "onLabel", "OFF");
    Blynk.setProperty(Widget_TimerButton_7, "offLabel", "OFF");
    Blynk.setProperty(Widget_TimerInput_7, "label", "TIMER 7 (OFF)");
  } else if (timer7Work == 1) {
    Blynk.setProperty(Widget_TimerButton_7, "onLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerButton_7, "offLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerInput_7, "label", "TIMER 7 (ZONE1)");

  } else if (timer7Work == 2) {
    Blynk.setProperty(Widget_TimerButton_7, "onLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerButton_7, "offLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerInput_7, "label", "TIMER 7 (ZONE2)");

  } else if (timer7Work == 3) {
    Blynk.setProperty(Widget_TimerButton_7, "onLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerButton_7, "offLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerInput_7, "label", "TIMER 7 (ZONE3)");
  }
    else if (timer7Work == 4) {
    Blynk.setProperty(Widget_TimerButton_7, "onLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerButton_7, "offLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerInput_7, "label", "TIMER 7 (ZONE4)");
  }
  else if (timer7Work == 5) {
    Blynk.setProperty(Widget_TimerButton_7, "onLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerButton_7, "offLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerInput_7, "label", "TIMER 7 (ALL ZONE)");
  }
}

void timer8Label() {
  if (timer8Work == 0) {
    Blynk.setProperty(Widget_TimerButton_8, "onLabel", "OFF");
    Blynk.setProperty(Widget_TimerButton_8, "offLabel", "OFF");
    Blynk.setProperty(Widget_TimerInput_8, "label", "TIMER 8 (OFF)");
  } else if (timer8Work == 1) {
    Blynk.setProperty(Widget_TimerButton_8, "onLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerButton_8, "offLabel", "ZONE1");
    Blynk.setProperty(Widget_TimerInput_8, "label", "TIMER 8 (ZONE1)");

  } else if (timer8Work == 2) {
    Blynk.setProperty(Widget_TimerButton_8, "onLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerButton_8, "offLabel", "ZONE2");
    Blynk.setProperty(Widget_TimerInput_8, "label", "TIMER 8 (ZONE2)");

  } else if (timer8Work == 3) {
    Blynk.setProperty(Widget_TimerButton_8, "onLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerButton_8, "offLabel", "ZONE3");
    Blynk.setProperty(Widget_TimerInput_8, "label", "TIMER 8 (ZONE3)");
  }
    else if (timer8Work == 4) {
    Blynk.setProperty(Widget_TimerButton_8, "onLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerButton_8, "offLabel", "ZONE4");
    Blynk.setProperty(Widget_TimerInput_8, "label", "TIMER 8 (ZONE4)");
  }
  else if (timer8Work == 5) {
    Blynk.setProperty(Widget_TimerButton_8, "onLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerButton_8, "offLabel", "ALL ZONE");
    Blynk.setProperty(Widget_TimerInput_8, "label", "TIMER 8 (ALL ZONE)");
  }
}
