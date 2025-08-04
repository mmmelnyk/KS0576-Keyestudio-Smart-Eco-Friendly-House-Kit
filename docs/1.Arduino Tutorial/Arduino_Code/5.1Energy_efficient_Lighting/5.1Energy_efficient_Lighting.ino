/*  
 * Filename    : Energy_efficient_Lighting
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
//Add the RGB6812 library file
#include <Adafruit_NeoPixel.h>

#define PIN 11      // The pin on the Arduino is connected to the NeoPixels.
#define NUMPIXELS 4 // Popular NeoPixel ring size.
Adafruit_NeoPixel  rgb_display(NUMPIXELS,PIN,NEO_GRB + NEO_KHZ800);  // Defining rgb_display functions.

int photoPin = A0; //Photoresistance
int pirPin = 10;   //PIR motion
int val = 0;   //The value of the Photoresistance sensor
int value = 0; //The value of the PIR motion sensor

void setup(){
  Serial.begin(9600);
  pinMode(pirPin,INPUT);
  pinMode(photoPin,INPUT);
  rgb_display.begin();    //Start 6812RGB
  rgb_display.setBrightness(100); //Set the brightness to 100. The value ranges from 0 to 255
}

void loop(){
  val = analogRead(photoPin);
  value = digitalRead(pirPin);
  Serial.print(val);
  Serial.print("  ");
  Serial.print(value);
  delay(100);
  if(val < 200 && value == 1){
    colorWipe(rgb_display.Color(255, 255, 255), 50); // On
    Serial.println("  Led on");
    delay(100);
  }else{
      colorWipe(rgb_display.Color(  0,   0,   0), 50); // Off
      Serial.println("  Led off");
      delay(100);
  }
}
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < rgb_display.numPixels(); i++) { //  For each pixel in strip...
    rgb_display.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    rgb_display.show();                          //  Update strip to match
    delay(wait);                                 //  Pause for a moment
  }
}
