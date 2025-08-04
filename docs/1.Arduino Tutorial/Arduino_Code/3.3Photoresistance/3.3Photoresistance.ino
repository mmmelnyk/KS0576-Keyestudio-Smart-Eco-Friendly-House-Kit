/*  
 * Filename    : Photoresistance
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
int val = 0;
int photoPin = A0;    //The pin of the Photoresistance
void setup() {
  Serial.begin(9600);       //Set baud rate
  pinMode(photoPin, INPUT); //Set input mode
}

void loop() {
  val = analogRead(photoPin); //Read the value of the sensor
  Serial.println(val);        //Print value
  delay(100);                 //delay 100ms
}