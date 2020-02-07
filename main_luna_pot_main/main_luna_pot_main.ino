#include <WiFi.h>          // Replace with WiFi.h for  ESP32 ESP8266 -> ESP8266WiFi.h
#include <WebServer.h>     // Replace with WebServer.h for ESP32 ESP8266 -> ESP8266WebServer.h
#include <AutoConnect.h>

WebServer Server;          // Replace with WebServer for ESP32 ESP8266 -> ESP8266WebServer
AutoConnect      Portal(Server);

void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
}

void loop() {
    Portal.handleClient();
}
