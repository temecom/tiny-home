/*
 * Read a String
 */

#include "tinyGarageDoor.h"

String  getSerialString(String prompt) {
  String readString; 

  Serial_.println(prompt); 
  
  // Wait for input
  while (!Serial_.available()) {}

  // Loop while input is coming in
 while (Serial_.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the String readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

}
