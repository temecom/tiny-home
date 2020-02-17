



/*************************************************************************
   Tiny Garage Door
   Door tilt indicator using the Tiny BMA250 shield

 ************************************************************************/

#include <Wire.h>         // For I2C communication with sensor
#include "BMA250.h"       // For interfacing with the accel. sensor
#include "tinyGarageDoor.h"

// Accelerometer sensor variables for the sensor and its values
BMA250 accel_sensor;
int x, y, z;
double temp;
int doorAxisValue;
int lastDoorAxisValue;
int percentOfFullTravel;
int doorMotion;
String doorState;



/**
   Set up the IO and serial port
*/
void setup() {
  Serial_.begin(BAUD_RATE_115200);
  Wire.begin();
  Serial_.print(F("Tiny-Garage Version: "));
  Serial_.println(F(VERSION));
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial_.print("Initializing BMA...");
  // Set up the BMA250 acccelerometer sensor
  accel_sensor.begin(BMA250_range_2g, BMA250_update_time_64ms);

  // Flash the led to indicate startup
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  
  // Set up the wifi
  initializeWifi(); 


}

void loop() {
  accel_sensor.read();//This function gets new data from the acccelerometer

  // Get the acceleration values from the sensor and store them into global variables
  // (Makes reading the rest of the program easier)
  x = accel_sensor.X;
  y = accel_sensor.Y;
  z = accel_sensor.Z;
  temp = ((accel_sensor.rawTemp * 0.5) + 24.0);

  // If the BMA250 is not found, nor connected correctly, these values will be produced
  // by the sensor
  if (x == -1 && y == -1 && z == -1) {
    // Print error message to Serial Monitor
    Serial_.print("ERROR! NO BMA250 DETECTED!");
  }

  else { // if we have correct sensor readings:
    showSerial();                 //Print to Serial Monitor or Plotter
  }


  // Report the accelerometer axis as the door position

  Serial_.print("Door: ");

  // Check the door state on the axis
  doorAxisValue = accel_sensor.DOOR_TILT_AXIS * BOARD_ORIENTATION;


  if (doorAxisValue > CLOSED_UPPER_THRESHOLD && doorAxisValue < OPEN_LOWER_THRESHOLD) {
    // In the middle
    doorMotion = doorAxisValue - lastDoorAxisValue; 
    if ( doorMotion> 0) {
      percentOfFullTravel = FULL_TRAVEL / (OPEN_LOWER_THRESHOLD - doorAxisValue);
      doorState = OPENING_STATE;
      
    } else {
      percentOfFullTravel =  FULL_TRAVEL / (doorAxisValue - CLOSED_UPPER_THRESHOLD);
      doorState = CLOSING_STATE;
    }

     
     ledFlash();
     Serial_.print(doorState);
     Serial_.print("(");
     Serial_.print(percentOfFullTravel);
     Serial_.println("%)");

  } else {
    if (doorAxisValue >= OPEN_LOWER_THRESHOLD) {
      // Fully open
      doorState = OPEN_STATE;
      ledOn();
    }

    if (doorAxisValue <= CLOSED_UPPER_THRESHOLD) {
      // Fully closed
      doorState = CLOSED_STATE;
      ledOff(); 

    }
    Serial_.println(doorState);
  }

  // Save the last
  lastDoorAxisValue = doorAxisValue;

  // Just a flash to indicate activite

  delay(500);
  // ***Without the delay, there would not be any sensor output***
}

// Prints the sensor values to the Serial Monitor, or Serial Plotter (found under 'Tools')
void showSerial() {
  Serial_.print("X = ");
  Serial_.print(x);

  Serial_.print("  Y = ");
  Serial_.print(y);

  Serial_.print("  Z = ");
  Serial_.print(z);

  Serial_.print("  Temperature(C) = ");
  Serial_.println(temp);
}

/**
 * Subroutine to toggle the led 
 */
void ledFlash() {
  // Flash LED when in 
  if (digitalRead(LED_BUILTIN) == HIGH) {
    digitalWrite(LED_BUILTIN, LOW); 
  } else {
    digitalWrite(LED_BUILTIN, HIGH); 
  }
}

/**
 * Turn the LED ON
 */

 void ledOn() {
  digitalWrite(LED_BUILTIN, HIGH); 
 }

 /**
  * Turn LED OFF
  */
  void ledOff() {
         digitalWrite(LED_BUILTIN, LOW); 
    
 }
