//******************************************************************************************//
//******************************************WEATHER*************************** *************//
//https://arduinojson.org/v6/assistant/ ---- Help Coding to extract json data

#ifdef WEATHER
void updateWeather() {
  HTTPClient http;
  //xoxo const size_t capacity = JSON_ARRAY_SIZE(3) + 2 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 3 * JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 340;
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + 2 * JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 270;
  DynamicJsonDocument doc(capacity);

  //Example Response
  /*{"coord": { "lon": 139,"lat": 35},
    "weather": [
      {
        "id": 800,
        "main": "Clear",
        "description": "clear sky",
        "icon": "01n"
      }
    ],
    "base": "stations",
    "main": {
      "temp": 281.52,
      "feels_like": 278.99,
      "temp_min": 280.15,
      "temp_max": 283.71,
      "pressure": 1016,
      "humidity": 93
    },
    "wind": {
      "speed": 0.47,
      "deg": 107.538
    },
    "clouds": {
      "all": 2
    },
    "dt": 1560350192,
    "sys": {
      "type": 3,
      "id": 2019346,
      "message": 0.0065,
      "country": "JP",
      "sunrise": 1560281377,
      "sunset": 1560333478
    },
    "timezone": 32400,
    "id": 1851632,
    "name": "Shuzenji",
    "cod": 200
    }
  */


  //xoxo http.begin(weatherHost + cityID + "&units=metric&appid=" + weatherKey);
  //Example Request
  //http://api.openweathermap.org/data/2.5/weather?lat=15.861429&lon=103.735252&appid=41e23158ecd42925c55103c967913367
  http.begin(weatherHost + "?lat=" + lat + "&lon=" + lon + "&appid=" + apiKey);
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
      delay(3000);
      return;
    }

    sprintf(lastupdateWheather, "%02d:%02d:%02d", hour(), minute(), second());

    JsonObject weather_0 = doc["weather"][0];
    String weather_0_id = weather_0["id"]; // 800
    const char* weather_0_main = weather_0["main"]; // "Clear"
    const char* weather_0_description = weather_0["description"]; // "clear sky"
    const char* weather_0_icon = weather_0["icon"]; // "01n"

    const char* base = doc["base"]; // "stations"

    JsonObject main = doc["main"];
    float main_temp = main["temp"]; // 281.52
    float main_feels_like = main["feels_like"]; // 278.99
    float main_temp_min = main["temp_min"]; // 280.15
    float main_temp_max = main["temp_max"]; // 283.71
    int main_pressure = main["pressure"]; // 1016
    int main_humidity = main["humidity"]; // 93

    float wind_speed = doc["wind"]["speed"]; // 0.47
    float wind_deg = doc["wind"]["deg"]; // 107.538

    int clouds_all = doc["clouds"]["all"]; // 2

    long dt = doc["dt"]; // 1560350192

    JsonObject sys = doc["sys"];
    int sys_type = sys["type"]; // 3
    long sys_id = sys["id"]; // 2019346
    float sys_message = sys["message"]; // 0.0065
    const char* sys_country = sys["country"]; // "JP"
    long sys_sunrise = sys["sunrise"]; // 1560281377
    long sys_sunset = sys["sunset"]; // 1560333478

    long timezone = doc["timezone"]; // 32400
    long id = doc["id"]; // 1851632
    const char* name = doc["name"]; // "Shuzenji"
    int cod = doc["cod"]; // 200
#ifdef  debugMode
    Serial.print("Weather Main : "); Serial.println(weather_0_id);
    Serial.print("Weather Main : "); Serial.println(weather_0_main);
    Serial.print("Weather Description : "); Serial.println(weather_0_description);
    Serial.print("icon : "); Serial.println(weather_0_icon);
    Serial.print("City : "); Serial.println(String(name));
    Serial.print("Temp : "); Serial.println(main_temp);
    Serial.print("Pressure : "); Serial.println(main_pressure);
    Serial.print("Humidity : "); Serial.println(main_humidity);
    Serial.print("Wind Speed : "); Serial.println(wind_speed);
    Serial.print("Wind Degree : "); Serial.println(wind_deg);
    Serial.print("Start With 5xx : "); Serial.println(weather_0_id.startsWith("5"));
#endif
    weatherMain = weather_0_id;
    weatherDescription = weather_0_description;
    weatherCity = String(name);

    temperatureData = main_temp-272.15;
    pressureData = main_pressure;
    humidityData = main_humidity;
    windspeedData = wind_speed;
    Blynk.virtualWrite(Widget_WeatherLocation, weatherCity);
    Blynk.virtualWrite(Widget_WeatherDescription, weatherDescription);

    

    //if startWith 8xx. It have rain  (https://openweathermap.org/weather-conditions)
    if ( weather_0_id.startsWith("5") ) {
      rainStatus = 1;
      rainStatusBlynkLed.on();
    } else {
      rainStatus = 0;
      rainStatusBlynkLed.off();
    }
#ifdef  debugMode
    Serial.print("Rain Status : "); Serial.println(rainStatus);
#endif
#ifdef ILI9341
    clearScreenData();
    displayDataSensor();
#endif

  } else {
    Serial.println("Error on HTTP request");
  }
  http.end();
}

#endif
