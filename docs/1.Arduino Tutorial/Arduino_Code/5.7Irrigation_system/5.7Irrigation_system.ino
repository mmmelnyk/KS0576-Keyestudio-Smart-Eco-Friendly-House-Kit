/*  
 * Filename    : Irrigation_system
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#include<LiquidCrystal_I2C.h>
#define RelayPin 5
#define BuzzerPin 6  //Define the buzzer pin
#define SoilHumidityPin A6
#define WaterLevelPin A7
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  pinMode(RelayPin,OUTPUT);
  pinMode(BuzzerPin,OUTPUT);
  pinMode(SoilHumidityPin,INPUT);
  pinMode(WaterLevelPin,INPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  int Svalue = analogRead(SoilHumidityPin);
  int Wvalue = analogRead(WaterLevelPin);

  lcd.clear();  //Clear
  lcd.display();
  lcd.setCursor(0, 0);      //Display soil moisture values
  lcd.print("SoilHum:");
  lcd.setCursor(9, 0);
  lcd.print(Svalue);
  lcd.setCursor(0, 1);
  lcd.print("WaterLevel:"); //Display water level value
  lcd.setCursor(11, 1);
  lcd.print(Wvalue);

  if(Wvalue <= 50)
  {
    tone(BuzzerPin,532);
    delay(100);
    tone(BuzzerPin,659);
    delay(100);
    noTone(BuzzerPin);   
  }
  else if(Svalue <= 100 && Wvalue >= 500)
  {
    digitalWrite(RelayPin,HIGH);
    delay(400);
    digitalWrite(RelayPin,LOW);
    delay(700);
  }
  delay(500);
}