/*  
 * Filename    : Driving_water_wheel
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
#define RelayPin 5
int ADkey = A2; //Define ADkey pins
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RelayPin,OUTPUT);
  pinMode(ADkey,INPUT);
}

void loop() {
  val = analogRead(ADkey); 
  if(700 <val && val <= 900)
  {
    digitalWrite(RelayPin,HIGH);
    delay(500);
  }    
  else
  {
    digitalWrite(RelayPin,LOW);
    delay(500);
  }
}