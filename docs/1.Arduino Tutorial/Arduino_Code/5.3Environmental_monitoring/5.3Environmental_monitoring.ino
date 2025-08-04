/*  
 * Filename    : Environmental_monitoring
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include "xht11.h"

unsigned char dht[4] = {0, 0, 0, 0}; //Only the first 32 bits of the data are received, not the parity bits.
int val = 0;
int photoPin = A0;    //The pin of the Photoresistance
int sensorValue;//Packet output from the sensor
long sum = 0;   
int vout = 0;   //vout is the processed data, that is, the output voltage of photocurrent of ultraviolet sensor
int uv = 0;     //UV Index
xht11 xht(9);

void setup() {
  Serial.begin(9600); //Open the serial monitor and set the baud rate to 9600.
  pinMode(photoPin, INPUT); //Set input mode
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  val = analogRead(photoPin); //Read the value of the sensor

  xht.receive(dht);

  sensorValue = 0;
  sum = 0;
  for(int i = 0 ; i < 1024 ; i++ )  //filter algorithm
  {  
      sensorValue = analogRead(A3); //Connect to pin A3
      sum = sensorValue + sum;
      delay(2);
  }
  vout = sum >> 10; //Start data processing
  vout = vout * 4980.0 / 1024;
 
  //The resulting photocurrent value is converted into an ultraviolet rating
  if(vout < 50){  
    uv = 0;
  }
  else if(vout < 227){
    uv = 1;
  }
  else if(vout < 318){
    uv = 2;
  }
  else if(vout < 408){
    uv = 3;
  }
  else if(vout < 503){
    uv = 4;
  }
  else if(vout < 606){
    uv = 5;
  }
  else if(vout < 696){
    uv = 6;
  }
  else if(vout < 795){
    uv = 7;
  }
  else if(vout < 881){
    uv = 8;
  }
  else if(vout < 976){
    uv = 9;
  }
  else if(vout < 1079){
    uv = 10;
  }
  else{
    uv = 11;
  }

  lcd.clear();  //Clear
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("TEMP:");
  lcd.setCursor(5,0);
  lcd.print(dht[2]);
  lcd.setCursor(10,0);
  lcd.print("H:");  
  lcd.setCursor(12,0);
  lcd.print(dht[0]);
  lcd.setCursor(0,1);
  lcd.print("ILL:");
  lcd.setCursor(4,1);
  lcd.print(val);
  lcd.setCursor(10,1);
  lcd.print("UV:");
  lcd.setCursor(13,1);
  lcd.print(uv);

}
