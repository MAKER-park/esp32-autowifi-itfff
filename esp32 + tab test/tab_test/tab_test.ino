#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "IFTTTWebhook.h"

#include <HTTPClient.h>
#include <string.h>

#define ADC_PIN         32 //soil
#define PIR_PIN         27 //PIR
#define SERVERIP        "110.15.108.4"//ip주소 나중에 외부 ip로 바꿀것 //192.168.35.93 내부 //110.15.108.4 외부

#include "DHT.h"
//here we use 14 of ESP32 to read data
#define DHTPIN 22
//our sensor is DHT11 type
#define DHTTYPE DHT11
//create an instance of DHT sensor
DHT dht(DHTPIN, DHTTYPE);


#define IFTTT_API_KEY "b1tS_dzyDEabsKWtS4woTJ"
#define IFTTT_EVENT_NAME "luna_pot"

#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            23

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

#define button1 39

int flag = 0;

float h = 0, t = 0;
int s = map(analogRead(ADC_PIN), 0, 4096, 100, 0);
int count = 0;
int pir_count = 10;


/* create a hardware timer */
hw_timer_t * timer = NULL;

void IRAM_ATTR onTimer() {
  pir_count++;
  count++;
  Serial.println(count);
  Serial.println(pir_count);
}



//neopixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second

void led(int n, int g, int r, int b) {
  for (int i = 0; i < n; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(g, r, b)); // Moderately brigh green/red/blue

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }

}

void pir_led() {
  Serial.println("motion!");
  led(8, 0, 0, 0);
  led(map(t, 0, 45, 0, 8), 20, 0, 0);
  delay(1000);
  led(8, 0, 0, 0);
  led(map(s, 0, 100, 0, 8), 0, 20, 0);
  delay(1000);
  led(8, 0, 0, 0);
  led(map(h, 0, 100, 0, 8), 0, 0, 20);
  delay(1000);
  led(8, 0, 0, 0);
}

void setup() {

  dht.begin();
  pinMode(PIR_PIN, INPUT);
  pinMode(button1, INPUT);
  Serial.begin(115200);
   //boot
  led(8, 100, 0, 0);
  led(8, 0, 100, 0);
  led(8, 0, 0, 100);
  led(8, 100, 100, 100);
  led(8, 0, 0, 0);

  
   WiFiManager wifiManager;
   wifiManager.autoConnect("Luna_pot");
   Serial.println("connected...yeey :)");
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  //send_event("luna_pot_temp");

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
  //boot
  led(8, 100, 0, 0);
  led(8, 0, 100, 0);
  led(8, 0, 0, 100);
  led(8, 100, 100, 100);
  led(8, 0, 0, 0);

  /* Use 1st timer of 4 */
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);
  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer, true);
  /* Set alarm to call onTimer function every second 1 tick is 1us
    => 1 second is 1000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 1000000, true);
  /* Start an alarm */
  timerAlarmEnable(timer);

  Serial.println("start timer");

}
