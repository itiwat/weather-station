//**************************************************************************************************//
//*********************************************MQTT*************************************************//

#ifdef CALENDAR

void mqttConnect() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(clientName, mqttUser, mqttPassword)) {
      Serial.println("connected");
      client.subscribe("espcalendar/todayschedule");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      mqttConnectCount++;
      if (mqttConnectCount > 5) {
        mqttMillis = currentMillis;
        mqttConnectCount = 0;
        mqttUpdate = 1;
      }
      
      delay(5000);
      return;
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");
  todaySchedule = "";
  int i = 0;
  while (i < length) todaySchedule += (char)payload[i++];
  Serial.print("today Schedule : "); Serial.println(todaySchedule);
  if (todaySchedule == "   ") todaySchedule = "no schedule to day :)";  
  tft.setCursor (0, 217);
  tft.setTextSize (2);
  tft.setTextColor (BLUE, BLACK);
  tft.print ("                           ");
  displayDataSensor();
}

#endif
