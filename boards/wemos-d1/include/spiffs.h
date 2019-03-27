#include <ArduinoJson.h>
#include "FS.h"

//READ

const char* readSpiffs(String data){

  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable.
  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }

  if (data == "ssid") return json["ssid"];
  if (data == "psw") return json["psw"];
  if (data == "dt") return json["delay_time"];
  if (data == "ts") return json["thingspeak_key"];
}


//SAVE

int saveConfig(const char* ssid, const char* psw, const char* delay_time, const char* thingspeak_key) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();


  if(ssid != NULL){
    json["ssid"] = ssid;
  }else if(psw != NULL){
    json["psw"] = psw;
  }else if(delay_time != NULL){
    json["delay_time"] = delay_time;
  }else if(thingspeak_key != NULL){
    json["thingspeak_key"] = thingspeak_key;
  }


  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  return 1;
}
