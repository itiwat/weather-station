//******************************************************************************************//
//******************************************TFT*********************************************//

#ifdef ILI9341
void drawUi() {
  tft.setCursor (230, 5);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("Wifi:");

  tft.setCursor (20, 30);
  tft.setTextSize (2);
  tft.setTextColor (GREEN, BLACK);
  tft.print ("Mode:");

  tft.setCursor (20, 50);
  tft.setTextSize (2);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("TEMP(C)");

  tft.setCursor (20, 100);
  tft.setTextSize (2);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("HUMIDITY(%)");

  tft.setCursor (20, 150);
  tft.setTextSize (2);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("PRESSURE");

  tft.setCursor (20, 200);
  tft.setTextSize (2);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("WIND SPEED");

  //tft.drawFastHLine(20, 130, 280, RED);
  tft.drawFastVLine(160, 40, 200, RED);
}

void displayButtonSet() {

  tft.setCursor (80, 30);
  tft.setTextSize (2);
  tft.setTextColor (BLUE, BLACK);
  if (modeSelect == 1) {
    tft.print ("MANUAL");
  } else if (modeSelect == 2) {
    tft.print ("AUTO  ");
  } else {
    tft.print ("TIMER ");
  }

  tft.setCursor (170, 30);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("RAIN Status : ");
  if (rainStatus == 1) {
    tft.setTextColor(BLUE, BLACK);
    tft.print ("YES");
  } else {
    tft.setTextColor(RED, BLACK);
    tft.print ("NO");
  }

  Serial.println("displayButtonSet");

}

void displayDataSet() {
  /*
    tft.setCursor(78, 135);
    tft.setTextSize(1);
    tft.setTextColor (WHITE, BLACK);
    tft.print("SET : ");
    tft.setTextColor(BLUE, BLACK);
    String strMoistureSet = String(moistureSet);
    if (moistureSet < 10) strMoistureSet = "0" + strMoistureSet;
    tft.print(moistureSet);
    tft.setTextColor (WHITE, BLACK);
    tft.print(" %");

    tft.setCursor(70, 145);
    tft.setTextSize(1);
    tft.setTextColor (WHITE, BLACK);
    tft.print("ZONE1 : ");
    tft.setTextColor(BLUE, BLACK);
    tft.print(autoWaterSprayDurationSet);
    tft.setTextColor (WHITE, BLACK);
    tft.print(" min");

    tft.setCursor(60, 175);
    tft.setTextSize(1);
    tft.setTextColor (WHITE, BLACK);
    tft.print("SENSOR R: ");
    tft.setTextColor(BLUE, BLACK);
    tft.print(sensorRoundSet);
    tft.setTextColor(WHITE, BLACK);
    tft.print(" min");

    tft.setCursor (275, 36);
    tft.setTextSize (1);
    tft.setTextColor (RED, BLACK);
    tft.print ("/ ");
    tft.print (temperatureSet);

    tft.setCursor (275, 76);
    tft.setTextSize (1);
    tft.setTextColor (YELLOW, BLACK);
    tft.print ("/ ");
    tft.print (lightSet);

    Serial.println("displayDataSet");
  */
}

void displayDataSensor() {

  tft.setCursor (20, 70);
  tft.setTextSize (2);
  tft.setTextColor (RED, BLACK);
  tft.print (temperatureData, 2);

  tft.setCursor (20, 120);
  tft.setTextSize (2);
  tft.setTextColor (CYAN, BLACK);
  tft.print (humidityData);

  tft.setCursor (20, 170);
  tft.setTextSize (2);
  tft.setTextColor (YELLOW, BLACK);
  tft.print (pressureData);

  tft.setCursor (20, 220);
  tft.setTextSize (2);
  tft.setTextColor (YELLOW, BLACK);
  tft.print (windspeedData);

  tft.setCursor (170, 50);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("WEATHER AT ");
  tft.setTextColor(BLUE, BLACK);
  tft.print (weatherCity);

  const int SCREEN_WIDTH = 320;
  int intTextLength = weatherDescription.length();
  if (intTextLength > 26) weatherDescription = weatherDescription.substring(0, 26);
  const char* text = weatherDescription.c_str();
  int textPosition = ((SCREEN_WIDTH + (SCREEN_WIDTH/2)) - (strlen(text) * 10)) / 2;
  tft.setCursor (textPosition, 60);
  tft.setTextSize (1);
  tft.setTextColor (MAGENTA, BLACK);
  weatherDescription.toUpperCase();
  tft.print (weatherDescription);

  tft.setCursor (170, 230);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("wheather update: ");
  tft.setTextColor(BLUE, BLACK);
  tft.print (lastupdateWheather);

  Serial.println("displayDataSensor");
 
}

void displayClock() {
  if ((currentMillis - runTime) > 500 ) {
    runTime = millis();
    dots = !dots;

    //Call every minute
    if (second() == 0) {
      getTime();
    }
    /* Blink LED
        if (zone1ValveStatus == 1) {
          digitalWrite(waterLed, dots);
        } else {
          digitalWrite(waterLed, LOW);
        }

        if (zone2ValveStatus == 1) {
          digitalWrite(sprayLed, dots);
        } else {
          digitalWrite(sprayLed, LOW);
        }
    */
    tft.setCursor(100, 5);
    tft.setTextColor(BLUE, BLACK);
    tft.setTextSize(1);
    tft.print(display_hour);
    if (dots) {
      tft.print(":");
    } else {
      tft.print(" ");
    }
    tft.print(display_minutes);
  }
}

void displayWifi() {
  int wifiDisplay = WifiPercentSignal();
  Blynk.virtualWrite(Widget_WifiDisplay, wifiDisplay);
  tft.setCursor(260, 5);
  tft.setTextColor(BLUE, BLACK);
  tft.setTextSize(1);
  tft.print(wifiDisplay);
  tft.setTextColor(WHITE, BLACK);
  tft.print("%");
}

int WifiPercentSignal() {
  CurrentWifiSignal = WiFi.RSSI();
  if (CurrentWifiSignal > -40) CurrentWifiSignal = -40;
  if (CurrentWifiSignal < -90) CurrentWifiSignal = -90;
  WifiSignal = map(CurrentWifiSignal, -40, -90, 100, 1);
  return WifiSignal;
}

void checkDisplayButtonSet() {
  if ((lastMode != modeSelect) || (lastZone1 != zone1ValveStatus) || (lastZone2 != zone2ValveStatus) || (lastZone3 != zone3ValveStatus) || (lastZone4 != zone4ValveStatus)
      || (lastRainDelay != rainDelayWork) ||
      (lastAutoZone1 != zone1AutoTimerWork) || (lastAutoZone2 != zone2AutoTimerWork)
      || (lastAutoZone3 != zone3AutoTimerWork) || (lastAutoZone4 != zone4AutoTimerWork)) {

    displayButtonSet();
    lastMode = modeSelect;
    lastZone1 = zone1ValveStatus;
    lastZone2 = zone2ValveStatus;
    lastZone3 = zone3ValveStatus;
    lastZone4 = zone4ValveStatus;
    lastRainDelay = rainDelayWork;
    lastAutoZone1 = zone1AutoTimerWork;
    lastAutoZone2 = zone2AutoTimerWork;
    lastAutoZone3 = zone3AutoTimerWork;
    lastAutoZone4 = zone4AutoTimerWork;
  }
}

void clearScreenData() {
  tft.setCursor (235, 20);
  tft.setTextSize (2);
  tft.setTextColor (RED, BLACK);
  tft.print ("     ");

  tft.setCursor (235, 60);
  tft.setTextSize (2);
  tft.setTextColor (YELLOW, BLACK);
  tft.print ("     ");

  tft.setCursor (235, 100);
  tft.setTextSize (2);
  tft.setTextColor (GREEN, BLACK);
  tft.print ("     ");

#ifdef ILI9341
  tft.setCursor (0, 205);
  tft.setTextSize (1);
  tft.setTextColor (BLUE, BLACK);
  tft.print ("                                     ");
#endif

}

#endif
