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
#include <Keypad.h>

int PIRPin = 10;    // The pin of the PIR motion
int PhotoPin = A0;  // The pin of the Photoresistance
int SoilHumidityPin = A6;
int WaterLevelPin = A7;
int RelayPin = 5;
int BuzzerPin = 6;
int UVPin = A3;

int PIRvalue = 0;   // PIR motion
int Photovalue = 0; // Photoresistance
unsigned char dht[4] = {0, 0, 0, 0}; // Only the first 32 bits of the data are received, not the parity bits.
long sum = 0;   
int vout = 0;       // vout is the processed data, that is, the output voltage of photocurrent of ultraviolet sensor
int uv = 0;         // UV Index
int sensorValue = 0;
bool residue0_led_status = false;      // Mission 0 led flag bit
bool residue0_led_status_last = false; // Mission 0 Last led flag bit
bool redLedOn = false;
bool blueLedOn = false;
bool greenLedOn = false;
bool pumpOn = false;
int pumpCycles = 0;
unsigned char tasks[5] = {'0', '1', '2', '3', '4'};
char currentTask = '0';

const byte ROWS = 4;
const byte COLS = 4;
// Connect keypad ROW0, ROW1, ROW2, ROW3 to these Arduino pins:
byte rowPins[ROWS] = {2, 3, 4, 7};
// Connect keypad COL0, COL1, COL2, COL3 to these Arduino pins:
byte colPins[COLS] = {8, 12, 13, A2};
// Define the keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Create the Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Startup melody function
void playStartupMelody() {
  // Define note frequencies (in Hz)
  int melody[] = {
    262,  // C4
    294,  // D4
    330,  // E4
    349,  // F4
    392,  // G4
    440,  // A4
    494,  // B4
    523   // C5
  };
  
  // Define note durations (in milliseconds)
  int noteDurations[] = {
    250, 250, 250, 250, 250, 250, 250, 500
  };
  
  // Play the melody
  for (int i = 0; i < 8; i++) {
    tone(BuzzerPin, melody[i], noteDurations[i]);
    delay(noteDurations[i] + 50); // Small pause between notes
    noTone(BuzzerPin);
  }
  
  delay(200); // Final pause
}

// LCD recovery function
void recoverLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  delay(100);
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
  
  // Play startup melody
  //playStartupMelody();
}

void loop() {
  char key = keypad.getKey();
  if(key)
  {
    Serial.print("You pressed ");
    Serial.println(key);
    if(isTask(key))
    {
      currentTask = key;
    }
    else{
      switch (key) {
        case 'A':
          if(currentTask == '1' && !redLedOn)
          {
            colorWipe(rgb_display.Color(255, 0, 0), 5);
            redLedOn = true;
            greenLedOn = false;
            blueLedOn = false;
          }
          else{
            colorWipe(rgb_display.Color(0, 0, 0), 5);
            redLedOn = false;
          }
          break;
        case 'B':
          if(currentTask == '1' && !greenLedOn)
          {
            colorWipe(rgb_display.Color(0, 255, 0), 5);
            greenLedOn = true;
            blueLedOn = false;
            redLedOn = false;
          }
          else{
            colorWipe(rgb_display.Color(0, 0, 0), 5);
            greenLedOn = false;
          }
          break;
        case 'C':
          if(currentTask == '1' && !blueLedOn)
          {
            colorWipe(rgb_display.Color(0, 0, 255), 5);
            blueLedOn = true;
            redLedOn = false;
            greenLedOn = false;
          }
          else{
            colorWipe(rgb_display.Color(0, 0, 0), 5);
            blueLedOn = false;
          }
          break;
        case '*':
          if(currentTask == '4')
          {
            if(!pumpOn) {
              pumpOn = true;
              pumpCycles = 0; // Reset cycle counter
            }
          }
          break;
        case '#':
          // LCD recovery key - press # if LCD gets stuck
          Serial.println("Recovering LCD...");
          recoverLCD();
          break;
        default:
          Serial.print("Other key: ");
          Serial.println(key);
          break;
      }
    }
  }
  
  switch (currentTask) {
    case '0':
      task0();
      break;
    case '1':
      task1();
      break;
    case '2':
      task2();
      break;
    case '3':
      task3();
      break;
    case '4':
      task4();
      break;
    default:
      Serial.print("Other key: ");
      Serial.println(key);
      break;
  }
}

bool isTask(char key)
{
  for (int i = 0; i < 5; i++) {
    if (tasks[i] == key) {
      return true;
    }
  }
  
  return false;
}

// Task 0: Light and PIR control
void task0() {
  static unsigned long lastLcdUpdate = 0;
  
  // Only update LCD every 500ms to reduce load
  if(millis() - lastLcdUpdate >= 500) {
    lcd.setCursor(0, 0);
    lcd.print("Task 0:PIR&Light");
    lastLcdUpdate = millis();
  }
  
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
void task1() {
  static unsigned long lastLcdUpdate = 0;
  
  // Only update LCD every 500ms to reduce load
  if(millis() - lastLcdUpdate >= 500) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Task 1: LED RGB");
    lastLcdUpdate = millis();
  }
  delay(200);
}

// Task 2: Display sensor data
void task2() {
  // Reset sum to prevent overflow
  sum = 0;
  
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
  
  // Add small delay before LCD operations
  delay(150);
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
  delay(150); // Increased delay for stability
}

// Task 3: Soil and water level monitoring
void task3() {
  int Svalue = analogRead(SoilHumidityPin); // Read soil humidity
  int Wvalue = analogRead(WaterLevelPin);  // Read water level

  // Add small delay before LCD operations
  delay(50);
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
  delay(150); // Increased delay for stability

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
void task4() {
  static unsigned long lastLcdUpdate = 0;
  
  // Only update LCD every 300ms to reduce interference
  if(millis() - lastLcdUpdate >= 300) {
    lcd.clear();  // Clear display
    lcd.display();
    lcd.setCursor(0, 0);
    lcd.print("Task 4: Pump");
    lastLcdUpdate = millis();
  }
  
  if(pumpOn && pumpCycles < 5)
  {
    digitalWrite(RelayPin, HIGH); // Relay on
    
    // Update pump status less frequently
    if(millis() - lastLcdUpdate >= 300) {
      lcd.setCursor(0, 1);
      lcd.print("Pump: ON ");
      lcd.print(pumpCycles + 1);
      lcd.print("/5");
    }
    
    delay(400);
    digitalWrite(RelayPin, LOW);
    pumpCycles++;
    
    // Turn off pump after 5 cycles
    if(pumpCycles >= 5) {
      pumpOn = false;
      pumpCycles = 0;
      // Small delay and LCD recovery after pump cycle
      delay(100);
      recoverLCD();
    }
  }
  else {
    digitalWrite(RelayPin, LOW);  // Relay off
    
    if(millis() - lastLcdUpdate >= 300) {
      lcd.setCursor(0, 1);
      lcd.print("Pump: OFF     "); // Extra spaces to clear old text
    }
  }
  delay(200); // Reduced delay for better responsiveness
}

// NeoPixel color wipe function
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < rgb_display.numPixels(); i++) { // For each pixel...
    rgb_display.setPixelColor(i, color);         // Set pixel's color (in RAM)
    rgb_display.show();                          // Update strip to match
    delay(wait);                                 // Pause for a moment
  }
}