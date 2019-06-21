#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "IFTTTWebhook.h"

#define ADC_PIN         32 //soil
#define PIR_PIN         21 //PIR

#include "DHT.h"
//here we use 14 of ESP32 to read data
#define DHTPIN 22
//our sensor is DHT11 type
#define DHTTYPE DHT11
//create an instance of DHT sensor
DHT dht(DHTPIN, DHTTYPE);

/*2019-04-07 이전것
#define IFTTT_Host "maker.ifttt.com"
#define IFTTT_KEY "b1tS_dzyDEabsKWtS4woTJ"
*/
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

int flag=0;

float h =0,t=0;


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second

void setup() {

  dht.begin();

  pinMode(PIR_PIN, INPUT);

  pinMode(button1, INPUT);
  
  Serial.begin(115200);

   WiFiManager wifiManager;


   wifiManager.autoConnect("Luna_pot");

   Serial.println("connected...yeey :)");
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket

    /*2019-04-07 new lib webhook
    IFTTTWebhook wh(IFTTT_API_KEY, IFTTT_EVENT_NAME);
    wh.trigger();
    wh.trigger("1");
    wh.trigger("1", "2");
    wh.trigger("1", "2", "3");
    */
    
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  //send_event("luna_pot_temp");  

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();

}
