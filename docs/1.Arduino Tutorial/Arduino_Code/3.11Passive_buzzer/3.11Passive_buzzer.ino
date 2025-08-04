/*  
 * Filename    : Passive_buzzer
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#define BuzzerPin 6  //Define the buzzer pin

void setup() {
  pinMode(BuzzerPin,OUTPUT);
}

void loop() {
  digitalWrite(BuzzerPin,HIGH);
  delayMicroseconds(500);  //delay500us
  digitalWrite(BuzzerPin,LOW);
  delayMicroseconds(500);  //delay500us
}