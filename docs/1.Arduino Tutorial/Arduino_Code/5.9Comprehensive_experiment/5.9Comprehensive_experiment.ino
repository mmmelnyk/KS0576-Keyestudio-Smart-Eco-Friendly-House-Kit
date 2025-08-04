/*  
 * Filename    : Comprehensive_experiment
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#include <Adafruit_NeoPixel.h>
#define PIN 11      // Pins on the Arduino that connect to the NeoPixels.
#define NUMPIXELS 4 // Popular NeoPixel ring size.
Adafruit_NeoPixel rgb_display(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  // Defining rgb_display functions.
#include "xht11.h"
xht11 xht(9);
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int PIRPin = 10;    // The pin of the PIR motion
int PhotoPin = A0;  // The pin of the Photoresistance
int ADkey = A2;     // Define ADkey pins
int SoilHumidityPin = A6;
int WaterLevelPin = A7;
int RelayPin = 5;
int BuzzerPin = 6;
int UVPin = A3;

int PIRvalue = 0;   // PIR motion
int Photovalue = 0; // Photoresistance
int ADvalue = 0;
unsigned char dht[4] = {0, 0, 0, 0}; // Only the first 32 bits of the data are received, not the parity bits.
long sum = 0;   
int vout = 0;       // vout is the processed data, that is, the output voltage of photocurrent of ultraviolet sensor
int uv = 0;         // UV Index
int sensorValue = 0;
int PushCounter = 0; // Stores the number of times a key is pressed

float val = 0;
float last_val = 0;
int press_key_index = 0; // 0-none 5-key5 4-key4 3-key3 1-key1
int sw1_press_num = 0;
int sw3_press_num = 0;
int sw4_press_num = 0;
int sw5_press_num = 0;
int filter_num = 100; // Sampling ADC data 100 times to determine the key value
int residue = 0;
bool residue0_led_status = false;      // Mission 0 led flag bit
bool residue0_led_status_last = false; // Mission 0 Last led flag bit

void key() {
  last_val = val;       // Update the last ADC value
  val = filter_ADkey(); // Update current ADC value
  if (val > 10 && abs(last_val - val) < 10) {
    if (900 < val) {
      press_key_index = 1;
      sw1_press_num++;
      sw5_press_num = 0;
      sw4_press_num = 0;
      sw3_press_num = 0;
    }
  }
  residue = sw1_press_num % 5;
  Serial.print("  Task");
  Serial.println(residue);
}

void setup() {
  Serial.begin(9600);     // Set baud rate
  rgb_display.begin();    // Start 6812RGB
  rgb_display.setBrightness(100); // Set the brightness to 5. The value ranges from 0 to 255
  colorWipe(rgb_display.Color(0, 0, 0), 5); // Initialize LED, turn off
  pinMode(PIRPin, INPUT);    // Set input mode
  pinMode(PhotoPin, INPUT);  // Set input mode
  pinMode(SoilHumidityPin, INPUT);
  pinMode(WaterLevelPin, INPUT);
  pinMode(RelayPin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  lcd.init();      // Initialize LCD
  lcd.backlight(); // Turn on backlight
  lcd.clear();     // Clear screen
}

void loop() {
  key();
  if (residue == 0) {
    residue0();
  } else if (residue == 1) {
    residue1();
  } else if (residue == 2) {
    residue2();
  } else if (residue == 3) {
    residue3();
  } else if (residue == 4) {
    residue4();
  }
}

// Task 0: Light and PIR control
void residue0() {
  lcd.setCursor(4, 0);
  lcd.print("Task 0");
  Photovalue = analogRead(PhotoPin);  // Read photoresistor value
  PIRvalue = digitalRead(PIRPin);    // Read PIR value
  Serial.print(Photovalue);
  Serial.print("  ");
  Serial.print(PIRvalue);
  delay(100);

  residue0_led_status_last = residue0_led_status; // Save last LED status
  if (PIRvalue == 1 && Photovalue <= 200) {
    residue0_led_status = true; // Turn on condition met
  } else {
    residue0_led_status = false; // Turn off condition met
  }
  
  // Execute when status changes
  if (residue0_led_status_last != residue0_led_status) {
    if (residue0_led_status) {
      colorWipe(rgb_display.Color(255, 255, 255), 50); // White on
      Serial.println("  Led on");
    } else {
      colorWipe(rgb_display.Color(0, 0, 0), 50); // Off
      Serial.println("  Led off"); 
    }
    delay(100);
  }
}

// Task 1: Button control RGB
void residue1() {
  lcd.setCursor(4, 0);
  lcd.print("Task 1");
  last_val = val;       // Update the last ADC value
  val = filter_ADkey(); // Update current ADC value

  /*  
    When the current ADC value is greater than 10 (a key is pressed) 
    and the absolute value of the difference between the last and 
    current ADC value is less than 10 (the key is pressed steadily)  
  */
  if (val > 10 && abs(last_val - val) < 10) {
    if (100 < val && val <= 300) {      // Key 5
      press_key_index = 5;
      sw5_press_num++;
      sw4_press_num = 0;
      sw3_press_num = 0;
      if (sw5_press_num % 2 == 1)       // Odd press count
        colorWipe(rgb_display.Color(255, 0, 0), 5); // Red 
      else
        colorWipe(rgb_display.Color(0, 0, 0), 5);   // Off
    } else if (300 < val && val <= 500) { // Key 4
      press_key_index = 4;
      sw4_press_num++;
      sw5_press_num = 0;
      sw3_press_num = 0;
      if (sw4_press_num % 2 == 1)
        colorWipe(rgb_display.Color(0, 255, 0), 5); // Green
      else
        colorWipe(rgb_display.Color(0, 0, 0), 5);   // Off
    } else if (500 < val && val <= 700) { // Key 3
      press_key_index = 3;
      sw3_press_num++;
      sw5_press_num = 0;
      sw4_press_num = 0;
      if (sw3_press_num % 2 == 1)
        colorWipe(rgb_display.Color(0, 0, 255), 5); // Blue
      else
        colorWipe(rgb_display.Color(0, 0, 0), 5);   // Off
    }
    Serial.println(val);  
    delay(200);
  } else if (val < 10) {
    press_key_index = 0;
  }
}

// Task 2: Display sensor data
void residue2() {
  Photovalue = analogRead(PhotoPin); // Read photoresistor value
  xht.receive(dht);                 // Read DHT11 data
  delay(100);
  
  // Filter algorithm
  for (int i = 0; i < 16; i++) {
    sensorValue = analogRead(UVPin); // Connect to pin A3
    sum = sensorValue + sum;
    delay(1);
  }
  vout = sum >> 4;                  // Data processing
  vout = vout * 4980.0 / 16;
 
  // Convert photocurrent to UV index
  if (vout < 50) {
    uv = 0;
  } else if (vout < 227) {
    uv = 1;
  } else if (vout < 318) {
    uv = 2;
  } else if (vout < 408) {
    uv = 3;
  } else if (vout < 503) {
    uv = 4;
  } else if (vout < 606) {
    uv = 5;
  } else if (vout < 696) {
    uv = 6;
  } else if (vout < 795) {
    uv = 7;
  } else if (vout < 881) {
    uv = 8;
  } else if (vout < 976) {
    uv = 9;
  } else if (vout < 1079) {
    uv = 10;
  } else {
    uv = 11;
  }

  Serial.print("  ");
  Serial.print(vout);
  Serial.print("  ");
  Serial.print(uv);
  lcd.clear();  // Clear display
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.setCursor(5, 0);
  lcd.print(dht[2]);
  lcd.setCursor(10, 0);
  lcd.print("H:");  
  lcd.setCursor(12, 0);
  lcd.print(dht[0]);
  lcd.setCursor(0, 1);
  lcd.print("ILL:");
  lcd.setCursor(4, 1);
  lcd.print(Photovalue);
  lcd.setCursor(10, 1);
  lcd.print("UV:");
  lcd.setCursor(13, 1);
  lcd.print(uv);
  delay(100);
}

// Task 3: Soil and water level monitoring
void residue3() {
  int Svalue = analogRead(SoilHumidityPin); // Read soil humidity
  int Wvalue = analogRead(WaterLevelPin);  // Read water level

  lcd.clear();  // Clear display
  lcd.display();
  lcd.setCursor(0, 0);      // Display soil humidity
  lcd.print("SoilHum:");
  lcd.setCursor(8, 0);
  lcd.print(Svalue);
  lcd.setCursor(0, 1);
  lcd.print("WaterLevel:"); // Display water level
  lcd.setCursor(11, 1);
  lcd.print(Wvalue);
  delay(100);

  if (Wvalue <= 50) {       // Low water level alarm
    tone(BuzzerPin, 532);
    delay(100);
    noTone(BuzzerPin);   
  } else if (Svalue <= 100 && Wvalue >= 500) { // Water plants if dry
    digitalWrite(RelayPin, HIGH);
    delay(500);
    digitalWrite(RelayPin, LOW);
    delay(500);
  }
}

// Task 4: Relay control
void residue4() {
  lcd.clear();  // Clear display
  lcd.display();
  lcd.setCursor(4, 0);
  lcd.print("Task 4");
  val = analogRead(ADkey); 
  if (700 < val && val <= 900) {
    digitalWrite(RelayPin, HIGH); // Relay on
  } else {
    digitalWrite(RelayPin, LOW);  // Relay off
  }
}

// NeoPixel color wipe function
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < rgb_display.numPixels(); i++) { // For each pixel...
    rgb_display.setPixelColor(i, color);         // Set pixel's color (in RAM)
    rgb_display.show();                          // Update strip to match
    delay(wait);                                 // Pause for a moment
  }
}

// AD key filtering function
float filter_ADkey(void) {
  int read_val[filter_num]; // Integer array to store ADC sequence
  int read_max = 0;      // Maximum value of ADC sequence
  int read_min = 1000;   // Minimum value of ADC sequence
  float read_return = 0; // Sum of ADC sequence

  // Read ADC values 100 times
  for (int i = 0; i < filter_num; i++) {
    read_val[i] = analogRead(ADkey); 
    delayMicroseconds(10);
  }

  // Find max/min and calculate sum
  for (int i = 0; i < filter_num; i++) {
    if (read_val[i] > read_max) 
      read_max = read_val[i];
    if (read_val[i] < read_min)
      read_min = read_val[i];
    read_return = read_return + read_val[i];
  }
  return (read_return - read_min - read_max) / (filter_num - 2); // Calculate average
}