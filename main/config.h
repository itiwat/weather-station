//**************************************************************************************************//
//******************************************SELECT OPTION*******************************************//

#define BLYNKLOCAL  //define if use blynk local server (option)
#define LINENOTIFY  //define if use linenotify (option)
#define WEATHER  //define if use weather and rain delay (option)
#define ILI9341  //define if use tftlcd (option)
#define PHYBUTTON  //define if use physical button (option)
//#define FIREBASE  //define if use firebase (option)
//#define CALENDAR  //define if use google calendar (option)

//**************************************************************************************************//
//**************************************************************************************************//

const char* ssid = "ssid";
const char* pass = "password";

#ifdef  BLYNKLOCAL
#define serverBlynk "blynk.iot-cm.com"
#define portBlynk 8080
const char* auth = "PnryTufj48jfj7N857PN85092385E598";  //blynk local
#else
const char* auth = "gk285LJOLrfff5984by5MSY25gt9eYBH";  //blynk official
#endif

//lora
byte localAddress = 0xA8;     // lora address of this device
byte destination = 0xA9;      // lora destination to send to

#ifdef LINENOTIFY                                               
#define LINE_TOKEN  "XDFTEGFumnglkhiNJUDujhgotypmuuiHETGDKFOnBGY"  //line token
#endif

#ifdef WEATHER
const String weatherHost = "http://api.openweathermap.org/data/2.5/weather?id=";
const char* weatherKey = "gh452jhyr25as96348ef52588rtgh6es7";  //weather key
const char* cityID = "1597591";  //koh samui
#endif

#ifdef FIREBASE
const char* firebaseHost = "myfarm-nx458.firebaseio.com";           
const char* firebaseAuth = "khjlMJHBHJS584521firtj584WJW,kfgp989245d";
#endif

#ifdef CALENDAR
const char* mqttServer = "soldier.cloudmqtt.com";
const int   mqttPort = 18887;
const char* mqttUser = "dkigmhkr";
const char* mqttPassword = "rgkkgihmhohkhb";
const char* clientName = "espmaster";
#endif
