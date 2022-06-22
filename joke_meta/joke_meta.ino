#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Wire.h>
#include <RealTimeClockDS1307.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <BH1750FVI.h>
#include "DHT.h"
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
SoftwareSerial mySerial(2, 3); // RX, TX

LiquidCrystal_I2C lcd(0x27, 20, 4);
unsigned long lux = 0;
unsigned long pre = 0;
void openFan(int state);
int s = 0, m = 0;
unsigned long previousMillis = 0;
unsigned long time = 0;
int _readTemp = 0;
int _readHumidity = 0;
long Millis = 0;
long interval = 1000;
int sec = 0;
const byte ROWS = 4; // four rows
const byte COLS = 3; // four columns
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

byte rowPins[ROWS] = {9, A3, A2, A0}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 8, A1};     // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int chackmemu = 0;
int address = 0;
void readFormMCU();
void read_time(void);
void getEPROM();
void setEPROM();
void readKeypad();
void working();
typedef struct
{           // the time record
  int hour; // hour
  int min;  // minute
  int sec;  // second
} TIMER;
TIMER realTime;
TIMER set_start1;
TIMER set_end1;
TIMER set_start2;
TIMER set_end2;
TIMER set_start3;
TIMER set_end3;
int readTemp = 0;
int readHum = 0;
unsigned long readLux = 0;
int set_temp_start, set_temp_end;
unsigned long set_lux_start = 0, set_lux_end = 0;
unsigned long previ = 0;
int checkWifi = 0;
int rond = 0;
int checkDoor = 1;
char key;
int reLayMotorR = 4;
int reLayMotorL = 5;
int pumpvax = 6;
int pumpwater = 7;
int reLayLed = 11;
int reLayFan = 12;
int led01 = 0;
bool statetime1 = false;
bool statetime2 = false;
int mode = 0;
int status_door = 0;
int status_evap = 0;
int status_light = 0;
int status_pumpwater = 0;
int sec1 = 0;
void checkWifi1();
void setTime()
{
  RTC.setHours(21);
  RTC.setMinutes(12);
  RTC.setSeconds(40);
  RTC.setClock();
}
void show_time(void)
{

  if (realTime.sec < 10)
  {
    lcd.setCursor(3, 0);
    lcd.print(realTime.hour);
    lcd.print(":");
    lcd.print(realTime.min);
    lcd.print(":");
    lcd.print((String) "0" + realTime.sec);
  }
  else if (realTime.min < 10)
  {
    lcd.setCursor(3, 0);
    lcd.print(realTime.hour);
    lcd.print(":");
    lcd.print((String) "0" + realTime.min);
    lcd.print(":");
    lcd.print(realTime.sec);
  }
  else if (realTime.hour < 10)
  {
    lcd.setCursor(3, 0);
    lcd.print((String) "0" + realTime.hour);
    lcd.print(":");
    lcd.print(realTime.min);
    lcd.print(":");
    lcd.print(realTime.sec);
  }
  else
  {
    lcd.setCursor(3, 0);
    lcd.print(realTime.hour);
    lcd.print(":");
    lcd.print(realTime.min);
    lcd.print(":");
    lcd.print(realTime.sec);
  }
}

void setup()
{
  // put your setup code here, to run once:
  // setTime();
  getEPROM();
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  mySerial.begin(9600);
  LightSensor.begin();
  Serial.println("test");
  Wire.begin();
  dht.begin();

  lcd.backlight();

  readFormMCU();
  pinMode(reLayMotorR, OUTPUT);
  pinMode(reLayMotorL, OUTPUT);
  pinMode(reLayFan, OUTPUT);
  pinMode(reLayLed, OUTPUT);
  pinMode(pumpvax, OUTPUT);
  pinMode(pumpwater, OUTPUT);
  getEPROM();
}

void loop()
{
  setEPROM();
  readFormMCU();
  readLux = LuxSensor();
  if (keypad.getKey())
  {
    lcd.clear();
    key = keypad.getKey();
    while (1)
    {

      mainmenu();
      readKeypad();
      setEPROM();
      if (key == '*')
      {
        lcd.clear();
        break;
      }
    }
  }
  else if (!keypad.getKey() || chackmemu == 0)
  {

    lcd.setCursor(3, 0);

    read_time();
    show_time();
    readSensor();
    working();
    setEPROM();
    unsigned long currentMillis = millis();
    int prev = 0;
    if (currentMillis - prev > 1000)
    {
      previ = currentMillis;
      sec1++;
      if (sec1 > 0 && sec1 < 3)
      {
        mySerial.println((String) "readLux=" + readLux);
      }
      else if (sec1 > 4 && sec1 < 5)
      {
        String time = (String)set_start1.hour + ":" + set_start1.min + "," + set_end1.hour + ":" + set_end1.min + "," + set_start2.hour + ":" + set_start2.min + "," + set_end2.hour + ":" + set_end2.min;
        mySerial.println((String) "time=" + time);
      }
      else if (sec1 > 5)
      {
        String setVal = (String)set_lux_start + "," + set_lux_end + "," + set_temp_start + "," + set_temp_end;
        mySerial.println((String) "setVal=" + setVal);
      }
      else if (sec1 > 6)
      {
        mySerial.println((String) "status=" + status_door + "," + status_evap + "," + status_light + "," + status_pumpwater);
      }
      else
      {

        sec1 = 0;
      }
    }
  }
}
unsigned long read_num(unsigned long nmax, int x, int y)
{
  chackmemu = 1;
  long num, i;
  lcd.setCursor(x, y);
  num = 0, i = 0;

  key = keypad.getKey();
  while (1)
  {
    do
    {
      key = keypad.getKey();
    } while (!key);
    if (key == '*' && i > -2)
    { // check key '*'
      x = x - 1;
      lcd.setCursor(x, y);
      lcd.print(" ");
      lcd.setCursor(x, y);
      num = num / 10;
      i = i - 1;
    }

    else if (key != '#' && key != '*')
    {
      if ((num * 10 + (key - 0x30)) <= nmax)
      {
        num = num * 10 + (key - 0x30);
        lcd.print(key);
        x = x + 1;
        i = i + 1;
      }
    }
    if (key == '#' || (i == -1 && key == '*'))
    {
      break;
    }
  }
  return (num);
}
String getSplit(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void readSensor()
{

  lcd.setCursor(3, 1);
  lcd.print("Humidity = ");
  lcd.setCursor(14, 1);
  lcd.print("      ");
  lcd.setCursor(14, 1);
  lcd.print(readHum);
  lcd.setCursor(3, 2);
  lcd.print("Temperature =");
  lcd.setCursor(17, 2);
  lcd.print("    ");
  lcd.setCursor(17, 2);
  lcd.print(readTemp);
  lcd.setCursor(3, 3);
  lcd.print("Lux = ");
  lcd.setCursor(9, 3);
  lcd.print("      ");
  lcd.setCursor(9, 3);
  lcd.print(readLux);
}
void read_time(void)
{
  RTC.readClock();
  realTime.hour = RTC.getHours();
  realTime.min = RTC.getMinutes();
  realTime.sec = RTC.getSeconds();
}
