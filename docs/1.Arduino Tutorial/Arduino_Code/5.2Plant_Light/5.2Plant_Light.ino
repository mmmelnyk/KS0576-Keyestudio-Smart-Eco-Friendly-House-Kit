/*  
 * Filename    : Plant_Light
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#include <Adafruit_NeoPixel.h>

#define PIN 11      // The pin on the Arduino is connected to the NeoPixels.
#define NUMPIXELS 4 // Popular NeoPixel ring size.
Adafruit_NeoPixel  rgb_display(NUMPIXELS,PIN,NEO_GRB + NEO_KHZ800);  // Defining rgb_display functions.

float val = 0;
float last_val = 0;
int press_key_index = 0; // 0-none 5-key5 4-key4 3-key3
int sw3_press_num  = 0;
int sw4_press_num  = 0;
int sw5_press_num  = 0;

int ADkey = A2; 
int filter_num = 100; // Sampling ADC data 100 times to determine the key value

void setup() {
  rgb_display.begin();  
  rgb_display.setBrightness(50); 
  colorWipe(rgb_display.Color(  0,   0,   0), 5); // Initialize LED, turn off
  Serial.begin(9600); 
}

void loop() {
  last_val = val;       // Update the last ADC value
  val = filter_ADkey(); // Update current ADC value

  /*  
    When the current ADC value is greater than 10 (a key is pressed) 
    and the absolute value of the difference between the last and 
    current ADC value is less than 10 (the key is pressed steadily)  
  */
  if (val>10 && abs(last_val-val)<10)
  {

    if (100 < val && val <= 300) {      // Key 5
      press_key_index = 5;
      /* 
        Update the number of times that key 5, 4, and 3 are pressed continuously. 
        If the same key is pressed again, different keys are cleared. 
      */    
      sw5_press_num++;
      sw4_press_num = 0;
      sw3_press_num = 0;
      if(sw5_press_num%2==1)  // key5 is pressed
        colorWipe(rgb_display.Color(255,   0,   0), 5); // Red 
      else
        colorWipe(rgb_display.Color(0,   0,   0), 5);
    } 
    else if (300 < val && val <= 500) { // Key 4
      press_key_index = 4;
      sw4_press_num++;
      sw5_press_num = 0;
      sw3_press_num = 0;
      if(sw4_press_num%2==1)
        colorWipe(rgb_display.Color(  0,   255,   0), 5); // Green
      else
        colorWipe(rgb_display.Color(0,   0,   0), 5);
    }
    else if (500 < val && val <= 700) { // Key 3
      press_key_index = 3;
      sw3_press_num++;
      sw5_press_num = 0;
      sw4_press_num = 0;
      if(sw3_press_num%2==1)
        colorWipe(rgb_display.Color(0,   0,   255), 5); // Blue 
      else
        colorWipe(rgb_display.Color(0,   0,   0), 5);
    }

    Serial.println(val);  
    // Serial.println(press_key_index);
    // Serial.println(last_press_key_index);
    // Serial.println(led_status);
    delay(200);
  }
  else if(val < 10){
    press_key_index = 0;
  }
 
}

void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < rgb_display.numPixels(); i++) { //  For each pixel in strip...
    rgb_display.setPixelColor(i, color);             //  Set pixel's color (in RAM)
    delay(wait);                                     //  Pause for a moment
  }
  rgb_display.show();                                //  Update strip to match
}

float filter_ADkey(void)  // Define a function that returns a float.
{
  int read_val[filter_num]; // Define an integer array with a length of 100 to store the ADC sequence.
  int read_max = 0;      // Define the maximum value of the ADC sequence
  int read_min = 1000;   // Define the minimum value of the ADC sequence
  float read_return = 0; // Define the sum of ADC sequences

  // Read the ADC value 100 times and store them in the sequence.
  for(int i = 0;i<filter_num;i++) 
  {
    read_val[i] = analogRead(ADkey); 
    delayMicroseconds(10);
  }

  // Find the maximum and minimum values in the ADC sequence and calculate the sum of the ADC values.
  for(int i = 0;i<filter_num;i++)
  {
    if(read_val[i]>read_max) 
      read_max = read_val[i];
    if(read_val[i]<read_min)
      read_min = read_val[i];
    read_return = read_return + read_val[i];
  }
  return (read_return-read_min-read_max)/(filter_num-2); // Find the average value of the ADC sequence
}