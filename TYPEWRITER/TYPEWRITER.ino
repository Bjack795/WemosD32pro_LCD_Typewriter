#include <SD.h>
#define ArrayCount(array) (sizeof array / sizeof array[0])
//ArrayCount(myarray) --> rows
//ArrayCount(myarray[0]) --> rows
/////////////////////////////////////////////////////////////////////////////////////////////
  #include <WiFi.h>              // Built-in
  #include <WiFiMulti.h>         // Built-in
  #include <ESP32WebServer.h>    // https://github.com/Pedroalbuquerque/ESP32WebServer download and place in your Libraries folder
  #include <ESPmDNS.h>
  #include "FS.h"
  
  #include "Network.h"
  #include "Sys_Variables.h"
  #include "CSS.h"
  #include <SD.h> 
  #include <SPI.h>
  WiFiMulti wifiMulti;
  ESP32WebServer server(80);
void Webserver_setup();
void Webserver_loop();
void copy_file(String pathold, String pathnew);
void cursor_file(String pathsave);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PIN_RX 33
#define PIN_TX 25
//devono essere pin digitali
int FLAG_ESC=0;
HardwareSerial Tastiera(1);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////SCREEN
#include "New_Characters.h"
#include <LiquidCrystal.h>
#define RS  14
#define E   12
#define D4  27
#define D5  26
#define D6  32
#define D7  15
#define A_PIN 5
LiquidCrystal lcd (RS,E,D4,D5,D6,D7);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String ANSWER;
File TEMPFILE;
File NEWFILE;
String PATHTEMP = "/Settings/temp.txt";
String PATHCURSOR = "/Settings/cursor_file.txt";
String PATHTESTI = "/Testi";
String PATHSETTINGS = "/Settings";

/////////////////////////////////////////////////
#define XRES 16
#define YRES 2
#define MAXLINES 200
int YPAG = 0, XCUR = 0, YCUR = 0;
/////////////////////////////////////////////////
int LEVEL = 0;
char MAIN_MENU [][XRES-2] = {"Open","New"};
char SAVE_MENU [][XRES-2] = {"Save","Don't save"};
int CHOSEN = 0;
int OPTION;
//////////////
char LISTA [50][XRES-2];
int LENG = 0;
int TITOLO;
int LAST_LEVEL;
int CRYPTO = -1;
String PREV_LOC;
int LINEE [MAXLINES];
int LINEE_LUNG = 0;
String TEXT_NAME;
bool IS_OLD;
int LENG_NEW = 0;
char entry_1[XRES];
/////////////////////////////

void setup() {
  Serial.begin(9600);
  Tastiera.begin(9600,SERIAL_8N1, PIN_RX, PIN_TX);
  Webserver_setup();
  ledcAttachPin(A_PIN, 1);
  ledcSetup(1, 12000, 8);
  lcd.createChar(0, ret_char);
  lcd.begin(XRES,YRES);
  if(!SD.exists(PATHSETTINGS))
  {
    SD.mkdir(PATHSETTINGS);

  }
   if(!SD.exists(PATHTESTI))
  {
    SD.mkdir(PATHTESTI);
  }
   if(!SD.exists(PATHCURSOR))
  {
    TEMPFILE = SD.open(PATHCURSOR, FILE_WRITE);
    TEMPFILE.close();
  }
 
}

void loop() {
  Webserver_loop();
  ledcWrite(1, 50);

  
  if (LEVEL == 0) //In the main menu
  { OPTION = choose_page(ArrayCount(MAIN_MENU), MAIN_MENU); 
    if(CHOSEN == 1)
    {
    if(OPTION == 0)
    {LEVEL = 100;} //choose the file
    else if(OPTION == 1)
    {LEVEL = 300;} //write the name of the new file

    
    }
    }

  
  else if (LEVEL > 99 and LEVEL <200) //choice of the file
  { if (CHOSEN == 1)
    {
      if((String)(MAIN_MENU[OPTION]) == "Open")
      { TITOLO = open_file("/Testi",&LENG,LISTA);
      }
        IS_OLD = true; //I'm opening a new file
     }
  }
  else if (LEVEL == 300) //I have to create a new file
    {
      LENG_NEW = insert_name(entry_1); 
      IS_OLD = false;
    }
  
  else if (LEVEL == 500) //inside a text
  {  if(IS_OLD == true) //I'm opening an existent file
      {
        TEXT_NAME = "/Testi/"+(String)(LISTA[TITOLO]);
        char text_name_char[TEXT_NAME.length()];
        TEXT_NAME.toCharArray(text_name_char,TEXT_NAME.length()+1); //string to char array
        cursor_file_read(text_name_char);
      }
    else //new file
    { 
      String entry_2; //char to string
      for (int i = 0; i<LENG_NEW;i++)
      {
        if((int)(entry_1[i])== 32) { entry_1[i] = (char)(95);}
        entry_2 +=entry_1[i];        
      }     
        TEXT_NAME = "/Testi/"+ entry_2 +".txt";
        char text_name_char[TEXT_NAME.length()];
        TEXT_NAME.toCharArray(text_name_char,TEXT_NAME.length()+1); //string to char
        cursor_file_save(text_name_char);
        NEWFILE = SD.open(TEXT_NAME, FILE_WRITE);
        NEWFILE.close();
        LAST_LEVEL = 0;
        XCUR = 0;
        YCUR = 0;
        YPAG = 0;
      
    }    
      print_page(TEXT_NAME);  
  }

  


}
