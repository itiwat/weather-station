//**************************************************************************************************//
//******************************************SELECT OPTION*******************************************//

#define BLYNKLOCAL  //define if use blynk local server (option)
//#define WEATHER  //define if use weather and rain delay (option)
#define ILI9341  //define if use tftlcd (option)
#define PHYBUTTON  //define if use physical button (option)
//#define FIREBASE  //define if use firebase (option)
//#define CALENDAR  //define if use google calendar (option)

//**************************************************************************************************//
//**************************************************************************************************//

const char* ssid = "@Prann_2.4G";
const char* pass = "@Asdfghjkl";

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
const String weatherHost = "http://api.openweathermap.org/data/2.5/weather?id=";
const char* weatherKey = "gh452jhyr25as96348ef52588rtgh6es7";  //weather key
const char* cityID = "1597591";  //koh samui
#endif
