/*  
 * Filename    : Light_on
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
//Add the RGB6812 library file
#include <Adafruit_NeoPixel.h>

#define PIN 11      // Pins on the Arduino that connect to the NeoPixels.
#define NUMPIXELS 4 // Popular NeoPixel ring size.
Adafruit_NeoPixel  rgb_display(NUMPIXELS,PIN,NEO_GRB + NEO_KHZ800);  // Defining rgb_display functions.

void setup() {
  rgb_display.begin();    //Start 6812RGB
  rgb_display.setBrightness(5); //Set the brightness to 5. The value ranges from 0 to 255
}

void loop() {
  rgb_display.setPixelColor(0, 255, 0, 0);     //The first lamp bead is bright red
  rgb_display.setPixelColor(1, 0, 255, 0);     //The second bead is bright green
  rgb_display.setPixelColor(2, 0, 0, 255);     //The third bead is bright blue
  rgb_display.setPixelColor(3, 255, 255, 255); //The fourth lamp bead is bright white
  rgb_display.show();   //Displays the color of the lamp bead
}