/*  
 * Filename    : LCD
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  lcd.setCursor(2,0);
  lcd.print("Hello World!");
  lcd.setCursor(2,1);
  lcd.print("Hello Keyes!");  
}