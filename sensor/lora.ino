void sendData() {
  String message = "";
  message +=  ";";
  message += temperatureData;  
  message +=  ";";
  message += moistureData;
  message +=  ";";
  message += fertilityData;
  message +=  ";";
  message += lightData;
  message +=  ";";
  message += batteryData;
  sendMessage(message);
    
  Serial.print("Temperature : "); Serial.println(temperatureData);
  Serial.print("battery : "); Serial.println(batteryData);
  Serial.print("Moisture : "); Serial.println(moistureData);
  Serial.print("fertility : "); Serial.println(fertilityData);
  Serial.print("light : "); Serial.println(lightData);
  Serial.print("update lora complete : "); Serial.println(message);
  Serial.print("millis : "); Serial.println(millis());
  sendMillis = millis();
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

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();

  sensorRoundSet = incoming.toInt();
  int sensorRoundSetTmp = EEPROM.read(SENSOR_ROUND_DURATION_SET_ADDRESS);
  if (sensorRoundSet != sensorRoundSetTmp) {
    EEPROM.write(SENSOR_ROUND_DURATION_SET_ADDRESS, sensorRoundSet);
    EEPROM.commit();
    Serial.print("eeprom write sensor round set : "); Serial.println(sensorRoundSet);
  }

  Serial.print("sensor round set : "); Serial.println(sensorRoundSet);
  hibernate();
}

void initLora() {
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  //LoRa.setTxPower(1);  //1-17
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa init succeeded.");
}
