/*

 This example connects to an unencrypted Wifi network.
 Then it prints the  MAC address of the Wifi shield,
 the IP address obtained, and other network details.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFi101.h>
#include "tinyGarageDoor.h"

char ssid[] = "yourNetwork";     //  your network SSID (name)
char pass[] = "secretPassword";  // your network password

// WPA configuration strings
//TODO: Save to flash 
String ssidString;
String passwordString; 

int status = WL_IDLE_STATUS;     // the Wifi radio's status

void initializeWifi() {

  // Needed for the tinyduino wifi shield
  WiFi.setPins(8,2,A3,-1);

  // Prompt for the WIFI settings
  ssidString = getSerialString("Enter your WIFI SSID");  

  passwordString = getSerialString("Enter your WIFI PASSWORD");
  
  //Initialize Serial_ and wait for port to open:
  while (!Serial_) {
    ; // wait for Serial_ port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial_.println("WiFi shield not present");
    return; 
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial_.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial_.print("Attempting to connect to WPA SSID: ");
    Serial_.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssidString.c_str(), passwordString.c_str());

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial_.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

}



void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial_.print("IP Address: ");
  Serial_.println(ip);
  Serial_.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial_.print("MAC address: ");
  Serial_.print(mac[5], HEX);
  Serial_.print(":");
  Serial_.print(mac[4], HEX);
  Serial_.print(":");
  Serial_.print(mac[3], HEX);
  Serial_.print(":");
  Serial_.print(mac[2], HEX);
  Serial_.print(":");
  Serial_.print(mac[1], HEX);
  Serial_.print(":");
  Serial_.println(mac[0], HEX);

}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial_.print("SSID: ");
  Serial_.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial_.print("BSSID: ");
  Serial_.print(bssid[5], HEX);
  Serial_.print(":");
  Serial_.print(bssid[4], HEX);
  Serial_.print(":");
  Serial_.print(bssid[3], HEX);
  Serial_.print(":");
  Serial_.print(bssid[2], HEX);
  Serial_.print(":");
  Serial_.print(bssid[1], HEX);
  Serial_.print(":");
  Serial_.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial_.print("signal strength (RSSI):");
  Serial_.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial_.print("Encryption Type:");
  Serial_.println(encryption, HEX);
  Serial_.println();
}
