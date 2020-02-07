void send_event(float temp, float hum, int soil) {
  char t[8];
  char h[8];
  char s[8];
  sprintf(t, "%.2f", temp);
  sprintf(h, "%.2f", hum);
  sprintf(s, "%d", soil);
  Serial.println(t);
  Serial.println(h);
  Serial.println(s);
  IFTTTWebhook wh(IFTTT_API_KEY, IFTTT_EVENT_NAME);
  wh.trigger(t, h, s);

  //mysql
  HTTPClient http;

  String endWeb = "http://110.15.108.4/lunapot_db_test1.php?temperature="; //주소 나중에 바꿀것!
  endWeb += String(t);
  endWeb += "&soil=";
  endWeb += String(s);
  endWeb += "&humidity=";
  endWeb += String(h);

  http.begin(endWeb);        
  Serial.println(endWeb);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error on HTTP request");
  }
  http.end();
  //pir_led();
  count = 0;
}


void dht_save() {
  //use the functions which are supplied by library.
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  /* print the result to Terminal
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  //we delay a little bit for next read*/
  delay(100);
}


void loop() {
  /*
    #define button1 39
  */
  // temp button 39!
  int pir = digitalRead(PIR_PIN);
 

  dht_save();
  if(count>=60){
   send_event(t, h, s); //ifttt+mysql data 추가 
  }
  //Serial.println(pir);
  if ( pir == HIGH) {
    if(pir_count>10){
               pir_led(); 
               pir_count=0;
    }
  }

}
