

//HTML pages handles

void handleConfig() {
  server.send ( 200, "text/html", CONFIG_HTML);
}

void handleRoot() {
  String htmlResponse = "<h1>Hello from airSensor powered by ESP8266</h1>  <h4>IP: " + WiFi.localIP().toString() + "</h4> <ap>Mac Address: " + String(WiFi.macAddress()) + "</h4> <h4>Actual delay time: " + read_String(1) + "</h4> <h4>RSSI: " + String(WiFi.RSSI()) + "</h4>";
  String htmlFooter = "<h2 style='color = red;'>Power by Riccardo Salemme</h2>";
  if(sensor_status == 1){
    htmlResponse = htmlResponse + "<h4>Sensor Status: active</h4>";
  }else{
    htmlResponse = htmlResponse + "<h4>Sensor Status: inactive</h4>";
  }
  int dt = read_String(1).toInt();

  server.send ( 200, "text/html", htmlResponse + htmlFooter);
}

void handleSave() {
  if (server.arg("ssid")!= "" && server.arg("psw")!= ""){
    Serial.println("SSID: " + server.arg("ssid"));
    writeString(10, server.arg("ssid"));

    Serial.println("PSW: " + server.arg("psw"));
    writeString(60, server.arg("psw"));

    //server.send ( 200, "text/html", "ok!");
    server.sendHeader("Location", String("/"), true);
    server.send ( 302, "text/plain", "");
    delay(16000);
    ESP.restart();
  }
  if (server.arg("dt")!= ""){
    Serial.println("Delay Time: " + server.arg("dt"));
    //int dt = atoi(server.arg("dt").c_str());
    //Serial.println(dt);
    writeString(1, server.arg("dt"));
    server.sendHeader("Location", String("/"), true);
    server.send ( 302, "text/plain", "");
    delay(16000);
    ESP.restart();
  }
  if (server.arg("ts_key")!= ""){
    Serial.println("ThingSpeak Key: " + server.arg("ts_key"));
    //int dt = atoi(server.arg("dt").c_str());
    //Serial.println(dt);
    writeString(150, server.arg("ts_key"));
    server.send ( 200, "text/html", "ok! Thingspeak Key setted");
    delay(6000);
    ESP.restart();
  }

}
