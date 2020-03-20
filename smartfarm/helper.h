//**************************************************************************************************//
//*********************************************HELPER***********************************************//

#define ONE_MINUTE 60000 // 1 minute

// define relay pins lora
#define waterValve 17  //water
#define sprayValve 16  //spray
#define valve3 4  //option
#define valve4 18  //option

//define physical button
#ifdef PHYBUTTON
#define manualButton 22  //33
#define modeButton 23  //32
#endif

//define led
#define waterLed 21
#define sprayLed 32

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
#define WATER_AUTO_TIMER_ADDRESS 48
#define SPRAY_AUTO_TIMER_ADDRESS 56
#define RAIN_DELAY_ADDRESS 64
#define TIMER1_ADDRESS 72
#define TIMER2_ADDRESS 80
#define TIMER3_ADDRESS 88
#define TIMER4_ADDRESS 96
#define TIMER5_ADDRESS 108
#define TIMER6_ADDRESS 112
#define TIMER7_ADDRESS 120
#define TIMER8_ADDRESS 128
#define SENSOR_ROUND_DURATION_SET_ADDRESS 136

//define blynk widger
#define Widget_Temperatuer V1
#define Widget_Moisture V2
#define Widget_Fertility V3
#define Widget_Light V4

#define Widget_SensorLabel V11
#define Widget_RainDelayLed V12
#define Widget_SprayLed V13
#define Widget_WaterLed V14
#define Widget_ModeButton V15
#define Widget_SprayButton V16
#define Widget_WaterButton V17

#define Widget_WaterAutoTimerInput V21
#define Widget_WaterAutoTimerButton V22
#define Widget_SprayAutoTimerInput V23
#define Widget_SprayAutoTimerButton V24
#define Widget_WaterSprayDurationSetSlide V25
#define Widget_RainDelayButton V26
#define Widget_LightSetSlide V27
#define Widget_LightLabel V28
#define Widget_TemperatureSetSlide V29
#define Widget_MoistureSetSlide V30
#define Widget_SensorRoundSetSlide V31

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
#define TFT_CLK 15
#define TFT_MISO 19
#define TFT_MOSI 33
#define TFT_CS 13
#define TFT_RST 12
#define TFT_DC 25

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
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
#endif
