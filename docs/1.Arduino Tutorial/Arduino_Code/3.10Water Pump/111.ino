/*  
 * Filename    : Relay
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#define RelayPin 5

void setup() {
  Serial.begin(9600);
  pinMode(RelayPin,OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    if(Serial.read() == 'd'){
      digitalWrite(RelayPin,HIGH);
      delay(500);
      digitalWrite(RelayPin,LOW);
      delay(500);
    }
  }
}