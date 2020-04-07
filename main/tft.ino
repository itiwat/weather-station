//******************************************************************************************//
//******************************************TFT*********************************************//

#ifdef ILI9341
int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme)
{
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option

  x += r; y += r;   // Calculate coords of centre of ring
  int w = r / 3;    // Width of outer ring is 1/4 of radius
  int angle = 150;  // Half the sweep angle of meter (300 degrees)
  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v
  byte seg = 3; // Segments are 3 degrees wide = 100 segments for 300 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring
  // Variable to save "value" text colour from scheme and set default
  int colour = BLUE;

  // Draw colour blocks every inc degrees
  for (int i = -angle + inc / 2; i < angle - inc / 2; i += inc) {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v) { // Fill in coloured segments with 2 triangles
      switch (scheme) {
        case 0: colour = RED; break; // Fixed colour
        case 1: colour = GREEN; break; // Fixed colour
        case 2: colour = BLUE; break; // Fixed colour
        case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
        case 4: colour = rainbow(map(i, -angle, angle, 70, 127)); break; // Green to red (high temperature etc)
        case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
        default: colour = BLUE; break; // Fixed colour
      }
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      //text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, GREY);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, GREY);
    }
  }
  // Convert value to a string
  char buf[10];
  byte len = 2; if (value > 999) len = 4;
  dtostrf(value, len, 0, buf);
  buf[len] = ' '; buf[len] = 0; // Add blanking space and terminator, helps to centre text too!
  // Set the text colour to default
  tft.setTextSize(1);

  if (value > 9) {
    tft.setTextColor(colour, BLACK);
    tft.setCursor(x - 25, y - 10); tft.setTextSize(5);
    tft.print(buf);
  }
  if (value < 10) {
    tft.setTextColor(colour, BLACK);
    tft.setCursor(x - 25, y - 10); tft.setTextSize(5);
    tft.print(buf);
  }

  // Calculate and return right hand side x coordinate
  return x + r;
}

unsigned int rainbow(byte value) {
  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits
  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}

float sineWave(int phase) {
  return sin(phase * 0.0174532925);
}

void drawUi() {
  tft.setCursor (2, 5);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("Wifi:");

  tft.setCursor (230, 5);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("TEMPERTURE (C)");

  tft.setCursor (230, 45);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("LIGHT (LUX)");

  tft.setCursor (230, 85);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("FERTILITY");

  tft.setCursor (230, 125);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("MODE");

  tft.setCursor (230, 165);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("ZONE1   ZONE2");
}

void displayButtonSet() {

  tft.setCursor (235, 140);
  tft.setTextSize (2);
  tft.setTextColor (BLUE, BLACK);
  if (modeSelect == 1) {
    tft.print ("MANUAL");
  } else if (modeSelect == 2) {
    tft.print ("AUTO  ");
  } else {
    tft.print ("TIMER ");
  }

  tft.setCursor (230, 180);
  tft.setTextSize (2);
  if (zone1ValveStatus == 1) {
    tft.setTextColor (GREEN, BLACK);
    tft.print ("ON  ");
  } else {
    tft.setTextColor (RED, BLACK);
    tft.print ("OFF ");
  }

  if (zone2ValveStatus == 1) {
    tft.setTextColor (GREEN, BLACK);
    tft.print ("ON ");
  } else {
    tft.setTextColor (RED, BLACK);
    tft.print ("OFF");
  }

  /*
    tft.setCursor (165, 205);
    tft.setTextSize (1);
    tft.setTextColor (WHITE, BLACK);
    tft.print ("AUTO : ");
    if ((zone2AutoTimerWork == 1) && (zone1AutoTimerWork == 1)) {
      tft.setTextColor(GREEN, BLACK);
      tft.print ("W/S ");
    } else if ((zone2AutoTimerWork == 1) && (zone1AutoTimerWork == 0)) {
      tft.setTextColor(GREEN, BLACK);
      tft.print ("-/W ");
    } else if ((zone2AutoTimerWork == 0) && (zone1AutoTimerWork == 1)) {
      tft.setTextColor(GREEN, BLACK);
      tft.print ("W/- ");
    } else {
      tft.setTextColor(RED, BLACK);
      tft.print ("-/- ");
    }
  */

  tft.setCursor (230, 205);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("RAIN DELAY ");
  if (rainDelayWork == 1) {
    tft.setTextColor(GREEN, BLACK);
    tft.print ("ON ");
  } else {
    tft.setTextColor(RED, BLACK);
    tft.print ("OFF");
  }

  Serial.println("displayButtonSet");

}

void displayDataSet() {

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

}

void displayDataSensor() {

  if (moistureData > 0) tesmod = 1;

  if (tesmod == 0) reading = 99;
  if (tesmod == 1) reading = moistureData;

  int xpos = 0, ypos = 5, gap = 4, radius = 52;
  xpos = 320 / 2 - 160, ypos = 0, gap = 100, radius = 105;
  ringMeter(reading, 0, 100, xpos, ypos, radius, "", RED2GREEN);

  tft.setCursor (235, 20);
  tft.setTextSize (2);
  tft.setTextColor (RED, BLACK);
  tft.print (temperatureData, 2);

  tft.setCursor (235, 60);
  tft.setTextSize (2);
  tft.setTextColor (YELLOW, BLACK);
  tft.print (lightData);

  tft.setCursor (235, 100);
  tft.setTextSize (2);
  tft.setTextColor (GREEN, BLACK);
  tft.print (fertilityData);

  tft.setCursor (60, 84);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("    MOISTURE   ");

  tft.setCursor(66, 165);
  tft.setTextSize(1);
  tft.setTextColor (WHITE, BLACK);
  tft.print("SENSOR-> ");
  if (sensorRoundStatus == 0) {
    tft.setTextColor(BLUE, BLACK);
  } else {
    tft.setTextColor(RED, BLACK);
  }
  tft.print(timeStamp);

  tft.setCursor(56, 185);
  tft.setTextSize(1);
  tft.setTextColor (WHITE, BLACK);
  tft.print("SENSOR B.: ");
  tft.setTextColor (BLUE, BLACK);
  tft.print(batteryData);
  tft.setTextColor (WHITE, BLACK);
  tft.print(" v.");

#ifdef CALENDAR

  const int SCREEN_WIDTH = 222;  //270
  int textLength = weatherDescription.length();
  if (textLength > 37) weatherDescription = weatherDescription.substring(0, 37);
  const char* text = weatherDescription.c_str();  //  maximum 37 char
  int textPosition = (SCREEN_WIDTH - (strlen(text) * 6)) / 2;
  tft.setCursor (textPosition, 205);
  tft.setTextSize (1);
  tft.setTextColor (MAGENTA, BLACK);
  weatherDescription.toUpperCase();
  tft.print (weatherDescription);

  const int SCREEN_WIDTHS = 270;
  textLength = todaySchedule.length();
  if (textLength > 26) todaySchedule = todaySchedule.substring(0, 26);
  text = todaySchedule.c_str();
  textPosition = (SCREEN_WIDTHS - (strlen(text) * 10)) / 2;
  tft.setCursor (textPosition, 217);
  tft.setTextSize (2);
  tft.setTextColor (GREEN, BLACK);
  todaySchedule.toUpperCase();
  tft.print (todaySchedule);

#else                                          //  else def

  tft.setCursor (2, 205);
  tft.setTextSize (1);
  tft.setTextColor (WHITE, BLACK);
  tft.print ("WEATHER AT ");
  tft.setTextColor(BLUE, BLACK);
  tft.print (weatherCity);

  const int SCREEN_WIDTH = 270;
  int intTextLength = weatherDescription.length();
  if (intTextLength > 26) weatherDescription = weatherDescription.substring(0, 26);
  const char* text = weatherDescription.c_str();
  int textPosition = (SCREEN_WIDTH - (strlen(text) * 10)) / 2;
  tft.setCursor (textPosition, 217);
  tft.setTextSize (2);
  tft.setTextColor (MAGENTA, BLACK);
  weatherDescription.toUpperCase();
  tft.print (weatherDescription);

#endif

  Serial.println("displayDataSensor");

}

void displayClock() {
  if ((currentMillis - runTime) > 500 ) {
    runTime = millis();
    dots = !dots;

    if (second() == 0) {
      getTime();
    }

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

    tft.setCursor(62, 57);
    tft.setTextColor(BLUE, BLACK);
    tft.setTextSize(3);
    tft.print(displayHour);
    if (dots) {
      tft.print(":");
    } else {
      tft.print(" ");
    }
    tft.print(displayMinute);
  }
}

void displayWifi() {
  int wifiDisplay = WifiPercentSignal();
  Blynk.virtualWrite(Widget_WifiDisplay, wifiDisplay);
  tft.setCursor(35, 5);
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
  if ((lastMode != modeSelect) || (lastZone1 != zone1ValveStatus) ||
      (lastZone2 != zone2ValveStatus) || (lastRainDelay != rainDelayWork) ||
      (lastAutoZone1 != zone1AutoTimerWork) || (lastAutoZone2 != zone2AutoTimerWork)) {

    displayButtonSet();
    lastMode = modeSelect;
    lastZone1 = zone1ValveStatus;
    lastZone2 = zone2ValveStatus;
    lastRainDelay = rainDelayWork;
    lastAutoZone1 = zone1AutoTimerWork;
    lastAutoZone2 = zone2AutoTimerWork;
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
