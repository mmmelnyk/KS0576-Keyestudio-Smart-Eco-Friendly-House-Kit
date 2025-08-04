/*  
 * Filename    : XHT11
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#include "xht11.h"

xht11 xht(9);

unsigned char dht[4] = {0, 0, 0, 0}; //Only the first 32 bits of the data are received, not the parity bits.
void setup() {
  Serial.begin(9600); //Open the serial monitor and set the baud rate to 9600.
}

void loop() {
  if (xht.receive(dht)) { //True returns true when checked correctly.
    Serial.print("RH:");
    Serial.print(dht[0]); //The integral part of humidity, DHT[1], is a fractional part series. Print (" % ");
    Serial.print("  Temp:");
    Serial.print(dht[2]); //The integral part of temperature, DHT[3], is the decimal part.
    Serial.println("C");
  } else {    //Read error
    Serial.println("sensor error");
  }
  delay(1000);  //It takes 1000ms to wait for the device to read.
}