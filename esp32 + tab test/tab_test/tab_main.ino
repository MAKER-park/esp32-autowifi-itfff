void led(int n, int g, int r, int b){
  for(int i=0;i<n;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(g,r,b)); // Moderately brigh green/red/blue
 
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  
}
/*
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
}*/

void send_event(float temp,float hum,int soil){
  char t[8];
  char h[8];
  char s[8];
  sprintf(t,"%.2f",temp);
  sprintf(h,"%.2f",hum);
  sprintf(s,"%d",soil);
  Serial.println(t);
  Serial.println(h);
  Serial.println(s);
  IFTTTWebhook wh(IFTTT_API_KEY, IFTTT_EVENT_NAME);
  wh.trigger(t,h,s);

  //mysql
    HTTPClient http;

    String endWeb ="http://192.168.35.93/lunapot_db_test1.php?temp=";//주소 나중에 바꿀것!
    endWeb += String(t);
    endWeb += "&soil=";
    endWeb += String(s);
    endWeb += "&hum=";
    endWeb += String(h);
 
    http.begin(endWeb);        // 서버 주소 
    Serial.println(endWeb);
    int httpCode = http.GET(); 

    if(httpCode>0){
        String payload = http.getString();
        Serial.println(payload);
    }else{
        Serial.println("Error on HTTP request");
    }
    http.end(); 
    delay(5000);
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
int s = map(analogRead(ADC_PIN), 0, 4096, 100, 0);
int pir = digitalRead(PIR_PIN);

    dht_save();
    send_event(t,h,s);//ifttt+mysql data 추가




if( pir == HIGH){
  led(map(t,0,45,0,8),20,0,0);
  delay(1000);
  led(8,0,0,0);
  led(map(s,0,100,0,8),0,20,0);
  delay(1000);
  led(8,0,0,0);
  led(map(h,0,100,0,8),0,0,20);
  delay(1000);
}
if( pir == LOW){
  led(8,0,0,0);
}
  /*led(22,0,0,0);
  delay(1000);
  led(5,0,0,100);//number, g,r,b
  delay(1000);*/
}
