//Wifi Connection Functiones

int check_networks(){
  int numberOfNetworks = WiFi.scanNetworks();
 
  for(int i =0; i<numberOfNetworks; i++){
 
      Serial.print("Network name: ");
      Serial.println(WiFi.SSID(i));
      Serial.print("Signal strength: ");
      Serial.println(WiFi.RSSI(i));
      Serial.println("-----------------------");

      if(String(WiFi.SSID(i)) == read_String(10)){
        Serial.println("wifi trovata");
        //break;
        return 1;
      }
  } 
}

//EEPROM String write/read functiones

void writeString(char add,String data){
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}

String read_String(char add){
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}


//AP/STA Functiones


void ap(){

  if(check_networks() != 1){
      Serial.println("error!");
      Serial.print("Configuring access point...");

      WiFi.mode(WIFI_AP);
      WiFi.softAP(ssid, password);
    
      IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);
      
      server.on ( "/", handleConfig);
      server.on ("/save", handleSave);
      server.begin();
      
      Serial.println ( "HTTP server started" );
  }else{
    sta();
  }
}

void sta(){

  Serial.println("Start STA client...");
  Serial.println();

  //WiFi.disconnect();
  
  WiFi.mode(WIFI_STA);
  WiFi.hostname("Sensor");      // DHCP Hostname (useful for finding device for static lease)
  WiFi.begin(read_String(10).c_str(), read_String(60).c_str());

//  IPAddress ip(192,168,1,128);  //Node static IP
//  IPAddress gateway(192,168,1,1);
//  IPAddress subnet(255,255,255,0);
//  WiFi.config(ip, gateway, subnet);

  int timed=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    timed++;
    if(timed > 30){
      Serial.println("Trppo tempo; nessuna risposta!");
      ap();
    }
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on ( "/", handleRoot );
  server.on ("/save", handleSave);
  server.on ("/config", handleConfig);
  server.begin();
}

//scd30 fnctiones

int scd30_read(){
  if (airSensor.dataAvailable()){
    
      String co2 = String(airSensor.getCO2());
      String t = String(airSensor.getTemperature(), 1);
      String h = String(airSensor.getHumidity(), 1);
  
      HTTPClient http;
      String request = "http://api.thingspeak.com/update?api_key="+ThingSpeakApiKey+"&field3=" + co2 + "&field4=" + t + "&field5=" + h; //HTTP!!!!
      //Serial.println(request);
      http.begin(request);
      int httpCode = http.GET();
      if (httpCode > 0) {
        String payload = http.getString();
        //Serial.println(payload);
        if(payload == "0"){
          http.end();
          return 0;
        }
      }
        http.end();
        return 1;
  }else{
    //Serial.println("No data");
    return 0;
  }
}
