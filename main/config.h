//**************************************************************************************************//
//******************************************SELECT OPTION*******************************************//

#define BLYNKLOCAL  //define if use blynk local server (option)
#define WEATHER  //define if use weather and rain delay (option)
#define ILI9341  //define if use tftlcd (option)
#define PHYBUTTON  //define if use physical button (option)
//#define FIREBASE  //define if use firebase (option)
//#define CALENDAR  //define if use google calendar (option)

//**************************************************************************************************//
//**************************************************************************************************//

const char* ssid = "@Prann_2.4G";
const char* pass = "@Asdfghjkl";

// Define NTP Client to get time
//For UTC -5.00 : -5 * 60 * 60 : -18000
//For UTC +1.00 : 1 * 60 * 60 : 3600
//For UTC +0.00 : 0 * 60 * 60 : 0
const char* ntpServer = "asia.pool.ntp.org";
const long  gmtOffset_sec = 25200;
const int   daylightOffset_sec = 0;

#ifdef  BLYNKLOCAL
#define serverBlynk "blynk.iot-cm.com"
//#define serverBlynk "192.168.1.199"
#define portBlynk 8080
const char* auth = "KEmRSqxNS03A17EVCVvOSaiOtLU2Vnj9";  //blynk local
#else
const char* auth = "gk285LJOLrfff5984by5MSY25gt9eYBH";  //blynk official
#endif

//lora
byte localAddress = 0xA8;     // lora address of this device
byte destination = 0xA9;      // lora destination to send to

#ifdef WEATHER
//api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={your api key}
//xoxo const String weatherHost = "http://api.openweathermap.org/data/2.5/weather?id=";
const String weatherHost = "http://api.openweathermap.org/data/2.5/weather";
const char* apiKey = "41e23158ecd42925c55103c967913367";  //weather key
//xoxo const char* cityID = "1597591";  //koh samui
const char* lat = "15.861429";
const char* lon = "103.735252";
#endif
