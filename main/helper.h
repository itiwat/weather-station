//**************************************************************************************************//
//*********************************************HELPER***********************************************//

#define ONE_MINUTE 60000 // 1 minute

//define physical button
#ifdef PHYBUTTON
  //define zoneButton
  #define zone1Button 22
  #define zone2Button 21
  #define zone3Button 32
  #define zone4Button 33
#endif

//define zoneValve
#define zone1Valve 25
#define zone2Valve 26
#define zone3Valve 27
#define zone4Valve 14

//xoxo
#ifdef PHYBUTTON
  #define manualButton 33  //33
  #define modeButton 14  //32
#endif
//oxox

// define relay pins lora
#define manualSwitch 13
#define autoSwitch 12
#define waterValve 17  //water
#define sprayValve 16  //spray
#define valve3 4  //option
#define valve4 27  //option

//define led
#define waterLed 22
#define sprayLed 21

//define SX1278
#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    433E6

//define eeprom
#define EEPROM_SIZE 512
#define FIRST_ADDRESS 0
#define MODE_SELECT_ADDRESS 8
#define TEMPERATURE_SET_ADDRESS 16
#define MOISTURE_SET_ADDRESS 24
#define LIGHT_SET_ADDRESS 32
#define AUTO_WATER_SPRAY_DURATION_SET_ADDRESS 40
#define ZONE1_AUTO_TIMER_ADDRESS 48
#define ZONE2_AUTO_TIMER_ADDRESS 56
#define ZONE3_AUTO_TIMER_ADDRESS 64
#define ZONE4_AUTO_TIMER_ADDRESS 72
#define RAIN_DELAY_ADDRESS 80
#define TIMER1_ADDRESS 88
#define TIMER2_ADDRESS 96
#define TIMER3_ADDRESS 104
#define TIMER4_ADDRESS 112
#define TIMER5_ADDRESS 120
#define TIMER6_ADDRESS 128
#define TIMER7_ADDRESS 136
#define TIMER8_ADDRESS 144
#define SENSOR_ROUND_DURATION_SET_ADDRESS 152

//define blynk widger
#define Widget_Temperatuer V1
#define Widget_Moisture V2
#define Widget_Fertility V3
#define Widget_Light V4
#define Widget_WifiDisplay V5
#define Widget_ManualControlDisplay V6

#define Widget_SensorLabel V11
#define Widget_RainDelayLed V12
#define Widget_ModeDisplay V13
#define Widget_WaterSprayDurationSetSlide V14
#define Widget_RainDelayButton V15
#define Widget_LightSetSlide V16
#define Widget_LightLabel V17
#define Widget_TemperatureSetSlide V18
#define Widget_MoistureSetSlide V19
#define Widget_SensorRoundSetSlide V20

#define Widget_Zone1Led V21
#define Widget_Zone1Button V22
#define Widget_Zone1AutoTimerInput V23
#define Widget_Zone1AutoTimerButton V24
#define Widget_Zone2Led V25
#define Widget_Zone2Button V26
#define Widget_Zone2AutoTimerInput V27
#define Widget_Zone2AutoTimerButton V28
#define Widget_Zone3Led V29
#define Widget_Zone3Button V30
#define Widget_Zone3AutoTimerInput V31
#define Widget_Zone3AutoTimerButton V32
#define Widget_Zone4Led V33
#define Widget_Zone4Button V34
#define Widget_Zone4AutoTimerInput V35
#define Widget_Zone4AutoTimerButton V36

#define Widget_TimerInput_1 V41
#define Widget_TimerInput_2 V42
#define Widget_TimerInput_3 V43
#define Widget_TimerInput_4 V44
#define Widget_TimerInput_5 V45
#define Widget_TimerInput_6 V46
#define Widget_TimerInput_7 V47
#define Widget_TimerInput_8 V48

#define Widget_TimerButton_1 V51
#define Widget_TimerButton_2 V52
#define Widget_TimerButton_3 V53
#define Widget_TimerButton_4 V54
#define Widget_TimerButton_5 V55
#define Widget_TimerButton_6 V56
#define Widget_TimerButton_7 V57
#define Widget_TimerButton_8 V58

#define Widget_TerminalBug V61

#ifdef ILI9341

  //define tft
  #define TFT_DC 4
  #define TFT_CS 15
  #define TFT_RST 2
  #define TFT_MISO 19         
  #define TFT_MOSI 23           
  #define TFT_CLK 18
  
  //vcc gnd cs reset d/c mosi sck led miso
  //        13 14    25  27   5       19
  
  // *** Define Name of Color
  #define BLACK   0x0000
  #define WHITE   0xFFFF
  #define RED     0xF800
  #define GREEN   0x07E0
  #define BLUE    0x001F
  #define CYAN    0x07FF
  #define MAGENTA 0xF81F
  #define YELLOW  0xFFE0
  #define GREY    0x2108
  
  // Meter colour schemes
  #define RED2RED 0
  #define GREEN2GREEN 1
  #define BLUE2BLUE 35
  #define BLUE2RED 3
  #define GREEN2RED 34
  #define RED2GREEN 5
  
  Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
#endif
