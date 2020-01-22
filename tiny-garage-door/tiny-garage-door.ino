
#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include "tinyGarageDoor.h"

void setup() {
   // Initialize Serial port
  Serial.begin(BAUD_RATE_115200);
  while (!Serial) continue;
  delay(2);
  Serial.print(F("Tiny-Garage Version: "));
  Serial.println(F(VERSION));
}

void loop() {
  Serial.println("Checking door... ");
  
  delay(1000); 
}
