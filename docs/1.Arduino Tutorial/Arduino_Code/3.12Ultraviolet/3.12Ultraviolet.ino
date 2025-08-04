/*  
 * Filename    : Ultraviolet
 * Arduino IDE : Arduino IDE 2.1.1
 * Auther      : http//www.keyestudio.com
*/
int sensorValue;//Packet output from the sensor
long sum = 0;   
int vout = 0;   //vout is the processed data, that is, the output voltage of photocurrent of ultraviolet sensor
int uv = 0;     //UV Index

void setup(){
Serial.begin(9600);
}

void loop()
{    
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
  Serial.print("The Photocurrent value : ");
  Serial.print(vout);
  Serial.println("mV");
 
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
  delay(20);
  Serial.print("UV Index = ");
  Serial.println(uv);
}