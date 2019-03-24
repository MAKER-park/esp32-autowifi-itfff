void led(int n, int g, int r, int b){
  for(int i=0;i<n;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(g,r,b)); // Moderately brigh green/red/blue
 
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  
}

void send_event(const char *event){
  Serial.print("Connecting to ");
  Serial.println(IFTTT_Host);
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(IFTTT_Host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += IFTTT_KEY;
  
  String mJson = String("{\"value1\":\"") +"10\"}";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
                       
  client.println(String("POST ") + url + " HTTP/1.1");
  client.println(String("Host: ") + IFTTT_Host);
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");  
  client.println(mJson.length());
  client.println();
  client.println(mJson);
 
  while(client.connected()){
    if(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    } else {
      delay(50);
    };
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
}


void loop() {
  led(22,0,0,0);
  delay(1000);
  led(5,0,0,100);//number, g,r,b
  delay(1000);
}
