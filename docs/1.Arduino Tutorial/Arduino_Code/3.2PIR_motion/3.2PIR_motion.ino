/*  
 * Filename    : PIR_motion
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
int value = 0;
int pirPin = 10; //The pin of the PIR motion
void setup() {
  Serial.begin(9600);     //Set baud rate
  pinMode(pirPin, INPUT); //Set input mode
}

void loop() {
  value = digitalRead(pirPin);  //Read the value of the sensor
  Serial.print(value);          //Print value
  if (value == 1) {  //There's someone nearby. Output high
    Serial.print("        ");
    Serial.println("Some body is in this area!");
    delay(100);
  }
  else {  //If no person is detected, the output is low
    Serial.print("        ");
    Serial.println("No one!");
    delay(100);
  }
}