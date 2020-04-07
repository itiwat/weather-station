//**************************************************************************************************************//
//*********************************************AUTO MODE********************************************************//

void autoCheck() {
  if ((sensorStatus == 1) && (rainStatus == 0)) {

    if ((currentMillis - autoMillis) <= (autoWaterSprayDurationSet * ONE_MINUTE)) {

      //auto zone1 check
      if ((zone1AutoTimerStatus  == 1) && (moistureData <= moistureSet)) {
        zone1ValveStatus = 1;
      }

      //auto zone2 check
      if ((zone2AutoTimerStatus  == 1) && (temperatureData >= temperatureSet) || (lightData >= lightSet)) {
        zone2ValveStatus = 1;
      }

      //auto zone3 check
      if ((zone3AutoTimerStatus  == 1) && (moistureData <= moistureSet)) {
        zone3ValveStatus = 1;
      }

      //auto zone4 check
      if ((zone4AutoTimerStatus  == 1) && (moistureData <= moistureSet)) {
        zone4ValveStatus = 1;
      }

    } else {
      closeAllValve();
    }

  } else {
    closeAllValve();
  }
}

//**************************************************************************************************************//
//**************************************AUTO TIMER INPUT********************************************************//

BLYNK_WRITE(Widget_Zone1AutoTimerInput) {  //  auto zone1 timer V21

  if ((modeSelect == 2) && (zone1AutoTimerWork == 1)) {

    sprintf(Date, "%02d/%02d/%04d",  day(), month(), year());
    sprintf(Time, "%02d:%02d:%02d", hour(), minute(), second());

    TimeInputParam t(param);

    Serial.print("Auto Zone1 Timer Checked schedule at: "); Serial.println(Time);
    terminal.print("Auto Zone1 Timer Checked schedule at: "); terminal.println(Time); terminal.flush();

    int dayadjustment = -1;  //  -1
    if (weekday() == 1) dayadjustment =  6;

    if (t.isWeekdaySelected(weekday() + dayadjustment)) {
      //Serial.println("Timer 5  ACTIVE today");
      if (t.hasStartTime()) //Serial.println(String("Start: ") + t.getStartHour() + ":" + t.getStartMinute());
        if (t.hasStopTime()) //Serial.println(String("Stop : ") + t.getStopHour() + ":" + t.getStopMinute());
          //Serial.println(String("Time zone: ") + t.getTZ());

          for (int i = 1; i <= 7; i++) {  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
            if (t.isWeekdaySelected(i)) {
              //Serial.println(String("Day ") + i + " is selected");
            }
          }

      nowseconds = ((hour() * 3600) + (minute() * 60) + second());
      startsecondswd = (t.getStartHour() * 3600) + (t.getStartMinute() * 60);
      //Serial.println(startsecondswd);
      if (nowseconds >= startsecondswd) {
        //Serial.print("Timer 5  STARTED at");
        //Serial.println(String(" ") + t.getStartHour() + ":" + t.getStartMinute());
        if (nowseconds <= startsecondswd + 90) {  // 90s on 60s timer ensures 1 trigger command is sent
          //digitalWrite(zone1Led, HIGH); // set LED ON
          zone1AutoTimerStatus = 1;
          // code here to switch the relay ON
        }
      }
      else {
        //Serial.println("Timer 5  NOT STARTED today");
      }

      stopsecondswd = (t.getStopHour() * 3600) + (t.getStopMinute() * 60);
      //Serial.println(stopsecondswd);

      if (nowseconds >= stopsecondswd) {
        //digitalWrite(zone1Led, LOW); // set LED OFF
        zone1AutoTimerStatus = 0;
        //Serial.print("Timer 5 STOPPED at");
        //Serial.println(String(" ") + t.getStopHour() + ":" + t.getStopMinute());
        if (nowseconds <= stopsecondswd + 90) { // 90s on 60s timer ensures 1 trigger command is sent
          //digitalWrite(zone1Led, LOW); // set LED OFF
          zone1AutoTimerStatus = 0;
          // code here to switch the relay OFF
        }
      }
      else {
        if (nowseconds >= startsecondswd) {
          //digitalWrite(zone1Led, HIGH); // set LED ON    test
          zone1AutoTimerStatus = 1;
          //Serial.println("Timer 5 is ON");
        }
      }
    }
    else {
      //Serial.println("Timer 5 INACTIVE today");
      // nothing to do today, check again in 30 SECONDS time
    }
    //Serial.println();
  }
}

BLYNK_WRITE(Widget_Zone2AutoTimerInput) {  //  auto water timer V23

  if ((modeSelect == 2) && (zone2AutoTimerWork == 1)) {

    sprintf(Date, "%02d/%02d/%04d",  day(), month(), year());
    sprintf(Time, "%02d:%02d:%02d", hour(), minute(), second());

    TimeInputParam t(param);

    Serial.print("Auto Zone2 Timer Checked schedule at: "); Serial.println(Time);
    terminal.print("Auto Zone2 Timer Checked schedule at: "); terminal.println(Time); terminal.flush();

    int dayadjustment = -1;  //  -1
    if (weekday() == 1) dayadjustment =  6;

    if (t.isWeekdaySelected(weekday() + dayadjustment)) {
      //Serial.println("Timer 5  ACTIVE today");
      if (t.hasStartTime()) //Serial.println(String("Start: ") + t.getStartHour() + ":" + t.getStartMinute());
        if (t.hasStopTime()) //Serial.println(String("Stop : ") + t.getStopHour() + ":" + t.getStopMinute());
          //Serial.println(String("Time zone: ") + t.getTZ());

          for (int i = 1; i <= 7; i++) {  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
            if (t.isWeekdaySelected(i)) {
              //Serial.println(String("Day ") + i + " is selected");
            }
          }

      nowseconds = ((hour() * 3600) + (minute() * 60) + second());
      startsecondswd = (t.getStartHour() * 3600) + (t.getStartMinute() * 60);
      //Serial.println(startsecondswd);
      if (nowseconds >= startsecondswd) {
        //Serial.print("Timer 5  STARTED at");
        //Serial.println(String(" ") + t.getStartHour() + ":" + t.getStartMinute());
        if (nowseconds <= startsecondswd + 90) {  // 90s on 60s timer ensures 1 trigger command is sent
          //digitalWrite(zone1Led, HIGH); // set LED ON
          zone2AutoTimerStatus = 1;
          // code here to switch the relay ON
        }
      }
      else {
        //Serial.println("Timer 5  NOT STARTED today");
      }

      stopsecondswd = (t.getStopHour() * 3600) + (t.getStopMinute() * 60);
      //Serial.println(stopsecondswd);

      if (nowseconds >= stopsecondswd) {
        //digitalWrite(zone1Led, LOW); // set LED OFF
        zone2AutoTimerStatus = 0;
        //Serial.print("Timer 5 STOPPED at");
        //Serial.println(String(" ") + t.getStopHour() + ":" + t.getStopMinute());
        if (nowseconds <= stopsecondswd + 90) { // 90s on 60s timer ensures 1 trigger command is sent
          //digitalWrite(zone1Led, LOW); // set LED OFF
          zone2AutoTimerStatus = 0;
          // code here to switch the relay OFF
        }
      }
      else {
        if (nowseconds >= startsecondswd) {
          //digitalWrite(zone1Led, HIGH); // set LED ON    test
          zone2AutoTimerStatus = 1;
          //Serial.println("Timer 5 is ON");
        }
      }
    }
    else {
      //Serial.println("Timer 5 INACTIVE today");
      // nothing to do today, check again in 30 SECONDS time
    }
    //Serial.println();
  }
}

BLYNK_WRITE(Widget_Zone3AutoTimerInput) {  //  auto zone3 timer V21

  if ((modeSelect == 2) && (zone3AutoTimerWork == 1)) {

    sprintf(Date, "%02d/%02d/%04d",  day(), month(), year());
    sprintf(Time, "%02d:%02d:%02d", hour(), minute(), second());

    TimeInputParam t(param);

    Serial.print("Auto Zone3 Timer Checked schedule at: "); Serial.println(Time);
    terminal.print("Auto Zone3 Timer Checked schedule at: "); terminal.println(Time); terminal.flush();

    int dayadjustment = -1;  //  -1
    if (weekday() == 1) dayadjustment =  6;

    if (t.isWeekdaySelected(weekday() + dayadjustment)) {
      //Serial.println("Timer 5  ACTIVE today");
      if (t.hasStartTime()) //Serial.println(String("Start: ") + t.getStartHour() + ":" + t.getStartMinute());
        if (t.hasStopTime()) //Serial.println(String("Stop : ") + t.getStopHour() + ":" + t.getStopMinute());
          //Serial.println(String("Time zone: ") + t.getTZ());

          for (int i = 1; i <= 7; i++) {  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
            if (t.isWeekdaySelected(i)) {
              //Serial.println(String("Day ") + i + " is selected");
            }
          }

      nowseconds = ((hour() * 3600) + (minute() * 60) + second());
      startsecondswd = (t.getStartHour() * 3600) + (t.getStartMinute() * 60);
      //Serial.println(startsecondswd);
      if (nowseconds >= startsecondswd) {
        //Serial.print("Timer 5  STARTED at");
        //Serial.println(String(" ") + t.getStartHour() + ":" + t.getStartMinute());
        if (nowseconds <= startsecondswd + 90) {  // 90s on 60s timer ensures 1 trigger command is sent
          //digitalWrite(zone3Led, HIGH); // set LED ON
          zone3AutoTimerStatus = 1;
          // code here to switch the relay ON
        }
      }
      else {
        //Serial.println("Timer 5  NOT STARTED today");
      }

      stopsecondswd = (t.getStopHour() * 3600) + (t.getStopMinute() * 60);
      //Serial.println(stopsecondswd);

      if (nowseconds >= stopsecondswd) {
        //digitalWrite(zone3Led, LOW); // set LED OFF
        zone3AutoTimerStatus = 0;
        //Serial.print("Timer 5 STOPPED at");
        //Serial.println(String(" ") + t.getStopHour() + ":" + t.getStopMinute());
        if (nowseconds <= stopsecondswd + 90) { // 90s on 60s timer ensures 1 trigger command is sent
          //digitalWrite(zone3Led, LOW); // set LED OFF
          zone3AutoTimerStatus = 0;
          // code here to switch the relay OFF
        }
      }
      else {
        if (nowseconds >= startsecondswd) {
          //digitalWrite(zone3Led, HIGH); // set LED ON    test
          zone3AutoTimerStatus = 1;
          //Serial.println("Timer 5 is ON");
        }
      }
    }
    else {
      //Serial.println("Timer 5 INACTIVE today");
      // nothing to do today, check again in 30 SECONDS time
    }
    //Serial.println();
  }
}
