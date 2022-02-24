#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>
#include <MicroGear.h>
#include <SoftwareSerial.h>
#include <BH1750FVI.h>



#include "DHT.h"
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(D7, D6);
int sec = 0;

const char *ssid = "KUY";
const char *password = "123456789xo0";
String ipAddr = "";
String RMUTi_Username = "jomphon.ka";
String RMUTi_Password = "joker2158.";

#define APPID "Jokeiot"
#define KEY "YykoWTP3PCI2xrB"
#define SECRET "1vwDh4mTk0WxS1xI0p4eyREmM"
#define ALIAS "esp8266"
WiFiManager wm;

WiFiClient client;
// Create the Lightsensor instance
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
int timer = 0;
MicroGear microgear(client);
String getSplit(String data, char separator, int index);
int set_temp = 0, set_lux_start = 0, set_lux_end = 0;
String timestart1, timeend1;
int _readTemp = 0;
int _readHumidity = 0;
int _readLux = 0;
String time1;
String time2;
String time3;
long previousMillis = 0;
long previousMillis1 = 0;
long previousMillis2 = 0;
long interval = 2500;


String Set_Lux;
String Set_Temp;
String status_all;

String timeall;
String setval;

/* If a new message arrives, do this */
uint16_t readLux() {

  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("lux= ");
  delay(100);
  Serial.println(lux);
  return lux;
}



int readHumidity() {
  int h = dht.readHumidity();
  Serial.print("h= ");

  Serial.println(h);
  return h;
}
int readTemperature() {
  int t = dht.readTemperature();
  Serial.print("t= ");
  //
  Serial.println(t);
  return t;
}
void onMsghandler(char *topic, uint8_t *msg, unsigned int msglen)
{
  String top = (String)topic;
  msg[msglen] = '\0';
  String message = (String)(char *)msg;
  Serial.print(top);
  Serial.print(" ");
  Serial.println(message);

  if (top == "/Jokeiot/joke/time1")
  {
    time1 = message;
    mySerial.println((String) "time1=" + time1);
  }
  else if (top == "/Jokeiot/joke/time2")
  {
    time2 = message;
    mySerial.println((String) "time2=" + time2);
  }
  else if (top == "/Jokeiot/joke/time3")
  {
    time3 = message;
    mySerial.println((String) "time3=" + time3);
  }

  else if (top == "/Jokeiot/joke/setLux")
  {
    Set_Lux = message;
    mySerial.println((String) "setLux=" + Set_Lux);
  }
  else if (top == "/Jokeiot/joke/setTemp")
  {

    Set_Temp = message;
    mySerial.println((String) "setTemp=" + Set_Temp);
  }
  else if (top == "/Jokeiot/joke/Door")
  {
    mySerial.println((String) "Door=" + message);
  }
  else if (top == "/Jokeiot/joke/light")
  {

    int light = message.toInt();
    mySerial.println((String) "light=" + light);
  }
  else if (top == "/Jokeiot/joke/Evap")
  {
    int Evap = message.toInt();
    mySerial.println((String) "Evap=" + Evap);
  }
  else if (top == "/Jokeiot/joke/pumpwater")
  {
    int pumpwater = message.toInt();
    mySerial.println((String) "pumpwater=" + pumpwater);
  }
  else if (top == "/Jokeiot/joke/readdata")
  {
    microgear.publish("/Jokeiot/timeall", timeall);
    delay(1000);
    microgear.publish("/Jokeiot/setall", setval);

  } else if (top == "/Jokeiot/joke/readsensor") {

    microgear.publish("/Jokeiot/getSensor", (String)_readLux + "," + _readTemp + "," + _readHumidity);
  }
  else if (top == "/Jokeiot/joke/readstatus") {
    microgear.publish("/Jokeiot/status", status_all);
  }
}


void onConnected(char *attribute, uint8_t *msg, unsigned int msglen)
{
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
  microgear.subscribe("/joke/+");
}

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  LightSensor.begin();
  dht.begin();


  bool res;
  res = wm.autoConnect("SetWiFi"); // password protected ap

  if (!res)
  {
    write_Temp();
    write_Humidity();
    write_Lux();


  }
  else
  {
    //if you get here you have connected to the WiFi

    microgear.on(MESSAGE, onMsghandler);
    microgear.on(CONNECTED, onConnected);
    microgear.init(KEY, SECRET, ALIAS);

    microgear.connect(APPID);

  }
}
void readFormUNO()
{

  if (mySerial.available())
  {
    String received = mySerial.readStringUntil('\n');



    if (!received.indexOf("status="))
    {
      status_all = received.substring(7);

    }
    if (!received.indexOf("time="))
    {
      Serial.println(received);
      timeall = received.substring(5);
    }
    if (!received.indexOf("setVal="))
    {
      Serial.println(received);
      setval = received.substring(7);
    }
    if (!received.indexOf("Reset"))
    {
      wm.resetSettings();
      ESP.restart();
    }
  }
}
void loop()
{
  write_Temp();
  write_Humidity();
  write_Lux();
  readFormUNO();
  if (microgear.connected())
  {

    microgear.loop();

    if (timer >= 1000)
    {


      delay(100);

      timer = 0;
    }
    else
      timer += 100;
  }
  else
  {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000)
    {
      microgear.connect(APPID);
      timer = 0;
    }
    else
      timer += 100;
  }
  delay(100);
}
void write_Lux() {
  unsigned long currentMillis = millis();
  _readLux =  readLux();
  if (currentMillis - previousMillis > 2000) {
    previousMillis = currentMillis;
    mySerial.println((String)"readLux=" + _readLux);
  }

}
void write_Humidity() {
  unsigned long currentMillis = millis();
  _readHumidity =  readHumidity();
  if (currentMillis - previousMillis1 > 2500) {
    previousMillis1 = currentMillis;
    mySerial.println((String)"readHumidity=" + _readHumidity);
  }

}
void write_Temp() {
  unsigned long currentMillis = millis();
  _readTemp =  readTemperature();

  if (currentMillis - previousMillis2 > 3000) {
    previousMillis2 = currentMillis;
    mySerial.println((String)"readTemp=" + _readTemp);
  }


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