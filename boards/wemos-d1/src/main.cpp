#include "spiffs.h"

void setup() {
  Serial.begin(115200);
  Serial.println();

  delay(1000);
  Serial.println("Mounting FS...");

  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  Serial.println(readSpiffs("ssid"));
  Serial.println(readSpiffs("ts"));

  delay(5000);

  // if (!saveConfig("","","ciao","")) {
  //   Serial.println("Failed to save config");
  // } else {
  //   Serial.println("Config saved");
  // }


  delay(5000);
}

void loop(){

}
