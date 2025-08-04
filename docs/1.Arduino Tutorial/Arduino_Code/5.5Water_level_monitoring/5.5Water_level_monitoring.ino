/*  
 * Filename    : Water_level_monitoring
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#define WaterLevelPin A7
#define BuzzerPin 6  //Define the buzzer pin
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  pinMode(WaterLevelPin,INPUT);
  pinMode(BuzzerPin,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  int ReadValue = analogRead(WaterLevelPin);
  lcd.clear();  //Clear
  lcd.display();
  lcd.setCursor(0, 0);
  lcd.print("WaterLevel:");
  lcd.setCursor(6, 1);
  lcd.print(ReadValue);

  if( ReadValue >= 500 )
  {
    tone(BuzzerPin,1500);
    delay(300);
    tone(BuzzerPin,1000);
    delay(300);
    noTone(BuzzerPin);  
  }
  else if ( ReadValue <= 50 )
  {
    tone(BuzzerPin,659);
    delay(1000);
    tone(BuzzerPin,532);
    delay(1000);
    noTone(BuzzerPin);  
  }
  else
  {
    noTone(BuzzerPin); 
    delay(1000);
  }
  
}