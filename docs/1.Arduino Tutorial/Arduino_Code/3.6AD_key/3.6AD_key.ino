/*  
 * Filename    : AD_Key
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
int val = 0;
int ADkey = A2; //Define ADkey pins
void setup() {
  Serial.begin(9600); 
}

void loop() {
  val = analogRead(ADkey);  
  Serial.print(val);  
  if (val <= 100) { //Val is less than or equal to 100 when no button is pressed
    Serial.println("   No key  is pressed");
  } else if (val <= 300) { //When key 5 is pressed,val is between 100 and 300
    Serial.println("   SW5 is pressed");
  } else if (val <= 500) { //When key 4 is pressed,val is between 300 and 500
    Serial.println("   SW4 is pressed");
  } else if (val <= 700) { //When key 3 is pressed,val is between 500 and 700
    Serial.println("   SW3 is pressed");
  } else if (val <= 900) { //When key 2 is pressed,val is between 700 and 900
    Serial.println("   SW2 is pressed");
  } else {  //When key 1 is pressed,val is greater than 900
    Serial.println("   SW1 is pressed");
  }
}