void led(int n, int g, int r, int b){
  for(int i=0;i<n;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(g,r,b)); // Moderately brigh green/red/blue
 
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  
}

void send_event(const char *event,int temp,int hum,int soil){
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
  
  String mJson = String("{\"value1\":\"") +temp+"\"}";
  
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

void dht_save(){
  //use the functions which are supplied by library.
h = dht.readHumidity();
// Read temperature as Celsius (the default)
t = dht.readTemperature();
// Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
// print the result to Terminal
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.println(" *C ");
//we delay a little bit for next read
delay(100);
}


void loop() {
/*  
#define button1 39
*/
// temp button 39!
int s =20;
if(digitalRead(button1) == LOW){
  if(flag==0){
    flag=1;
    dht_save();
    send_event("luna_pot",t,h,s);
  }
}
else{
  flag=0;
}

  /*led(22,0,0,0);
  delay(1000);
  led(5,0,0,100);//number, g,r,b
  delay(1000);*/
}
