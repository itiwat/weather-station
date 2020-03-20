//**************************************************************************************************//
//*******************************************LORA***************************************************//

void initLora() {
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  LoRa.setTxPower(1);  //1-17

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa init succeeded.");
}

void sendData() {
  sendMessage(String(sensorRoundSet));
  Serial.print("Sending Sensor Round Set : "); Serial.print(sensorRoundSet);  Serial.println(" minute");
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xA9) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  Serial.println(); Serial.println("************Recieve Data Frome Sensor************");

  sendData();

  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));

  temperatureData = getValue(incoming, ';', 1).toFloat();
  moistureData = getValue(incoming, ';', 2).toInt();
  fertilityData = getValue(incoming, ';', 3).toInt();
  lightData = getValue(incoming, ';', 4).toInt();
  batteryData = getValue(incoming, ';', 5).toFloat();

  Serial.print("temperature : "); Serial.print(temperatureData); Serial.println("°C ");
  Serial.print("fertility : "); Serial.print(fertilityData); Serial.println(" us/cm ");
  Serial.print("moisture : "); Serial.print(moistureData); Serial.println("%H ");
  Serial.print("light : "); Serial.print(lightData); Serial.println(" lux ");
  Serial.print("battery : "); Serial.print(batteryData); Serial.println(" Volt ");
  Serial.println("recieve data from sensor success");

  resetSensor();
  if (modeSelect != 1) forceStopAllValve();

  getTime();
  timeStamp = displayHour + ":" + displayMinute;
  Blynk.virtualWrite(Widget_SensorLabel, displayHour + ":" + displayMinute);
  syncAllBlynk();
  autoMillis = currentMillis;
  sensorRoundMillis = currentMillis;
  firstDisplay = 0;
  sensorStatus = 1;
  updateBlynk();

#ifdef WEATHER
  updateWeather();
#else                             //elsedef no weather
#ifdef ILI9341
  clearScreenData();
  displayDataSensor();
#endif
#ifdef CALENDAR
  client.publish((baseTopic + "requestschedule").c_str(), "GET");
#endif
#ifdef LINENOTIFY
  lineNotifySensor();
#endif
#ifdef FIREBASE
  sendFirebase();
#endif
#endif

}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//******************************************************************************************//
//******************************************WEATHER*************************** *************//

#ifdef WEATHER
void updateWeather() {
  HTTPClient http;
  const size_t capacity = JSON_ARRAY_SIZE(3) + 2 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 3 * JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 340;
  DynamicJsonDocument doc(capacity);

  http.begin(weatherHost + cityID + "&units=metric&appid=" + weatherKey);
  int httpCode = http.GET();

  String payload;
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      delay(120000);
      return;
    }

    JsonObject weather_0 = doc["weather"][0];
    const char* weather_0_main = weather_0["main"];
    const char* weather_0_description = weather_0["description"];
    JsonObject main = doc["main"];
    const char* name = doc["name"];

    weatherMain = String(weather_0_main);
    weatherDescription = String(weather_0_description);
    weatherCity = String(name);

    Serial.print("Weather Main : "); Serial.println(weatherMain);
    Serial.print("Weather Description : "); Serial.println(weatherDescription);
    Serial.print("Weather City : "); Serial.println(weatherCity);

    if ((rainDelayWork == 1) && ((weatherMain == "Rain") || (weatherDescription == "thunderstorm with light rain") ||
                                 (weatherDescription == "thunderstorm with rain") || (weatherDescription == "thunderstorm with heavy rain") ||
                                 (weatherDescription == "light intensity drizzle rain") || (weatherDescription == "drizzle rain") ||
                                 (weatherDescription == "heavy intensity drizzle rain") || (weatherDescription == "shower rain and drizzle") ||
                                 (weatherDescription == "heavy shower rain and drizzle"))) {
      rainStatus = 1;
    } else {
      rainStatus = 0;
    }

    Serial.print("Rain Status : "); Serial.println(rainStatus);

#ifdef CALENDAR
    client.publish((baseTopic + "requestschedule").c_str(), "GET");
#endif
#ifdef ILI9341
    clearScreenData();
    displayDataSensor();
#endif
#ifdef LINENOTIFY
    lineNotifySensor();
#endif
#ifdef FIREBASE
    sendFirebase();
#endif

  } else {
    Serial.println("Error on HTTP request");
  }
  http.end();
}

#endif

//**************************************************************************************************//
//*******************************************firebase***********************************************//

#ifdef FIREBASE

void sendFirebase() {
  Firebase.begin(firebaseHost, firebaseAuth);
  Firebase.pushFloat(firebaseData, "temperature", temperatureData, 2);
  Firebase.pushInt(firebaseData, "moisture", moistureData);
  Firebase.pushInt(firebaseData, "fertility", fertilityData);
  Firebase.pushInt(firebaseData, "light", lightData);
  Firebase.pushFloat(firebaseData, "battery", batteryData, 2);
  Firebase.pushString(firebaseData, "time", timeStamp);
  Serial.println("update firebase complete");
}

#endif
