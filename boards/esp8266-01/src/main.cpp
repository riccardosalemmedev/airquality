//esp8266 libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//eeprom libraries
#include <EEPROM.h>

//scd30 libraries
#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h>

#include <myeeprom.h>

int sensor_status = 0;

int lastSampleTime = 0;
String ThingSpeakApiKey = "EBZG6LZT1GXJ0YXK";
int delay_time = 15000; //1 minuto

const char *ssid = "ProjectWork"; //NOME E PSW ACCESS-POINT
const char *password = "abcabcabc";

//my includes
#include "index_html.h " //html page


ESP8266WebServer server(80);
SCD30 airSensor;

#include "handles.h"
#include "functiones.h"

void setup() {
  Wire.begin(0,2);
  EEPROM.begin(512);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Provo a connettermi al WIFI (credenziali salvate nella EEPROM)");

  WiFi.persistent(false);

  _start();

  airSensor.begin(); //This will cause readings to occur every two seconds
  delay(5000);
}


void loop() {

  server.handleClient();

  int currentMillis = millis();
  yield();

  if (currentMillis > lastSampleTime){

    if(WiFi.status()== WL_CONNECTED){
      if(!scd30_read() == 1){
        Serial.println("ERROR: Sensor data is unattainable or delay time is too small (min. delay for Thingspeak is 15 sec.)");
        sensor_status = 0;
      }else{
        sensor_status = 1;
      }
    }else{
        Serial.println("Error in WiFi connection");
        delay(2000);
    }
    //Serial.println(lastSampleTime);
    lastSampleTime = currentMillis + read_String(1).toInt()*1000;
    //Serial.println(lastSampleTime);
    Serial.println("____________________________");
    yield();
  }
}
