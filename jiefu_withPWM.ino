#include <Wire.h>
float Current_Contorl[4];
char t_Valve_State[4][7];
float seg1, seg2, seg3, seg4;
//I2C
#define SLAVE_ADDRESS1 0x67
#define SLAVE_ADDRESS2 0x68
#define SLAVE_ADDRESS3 0x69
#define SLAVE_ADDRESS4 0x70


byte byteRead;

void setup() {
  Wire.begin();
  Serial.begin(9600);
//  Current_Contorl[0] = 1.1;
//  Current_Contorl[1] = 1.1;
//  Current_Contorl[2] = 1.1;
//  Current_Contorl[3] = 1.1;
}

void loop() {
  if (Serial.available()){

    byteRead = Serial.read();


    if(byteRead== 65) //A
    {
    Serial.println("Input seg1:");
     while(Serial.available()<=0) {
      }
      if(Serial.available())
      {
          seg1 = Serial.parseFloat();
      }
      ////////////////////////////
      Serial.println("Input seg2:");
     while(Serial.available()<=0) {
      }
      if(Serial.available())
      {
          seg2 = Serial.parseFloat();
      }
      ////////////////////////////      
      Serial.println("Input seg3:");
     while(Serial.available()<=0) {
      }
      if(Serial.available())
      {
          seg3 = Serial.parseFloat();
      }
      ////////////////////////////      
      Serial.println("Input seg4:");
     while(Serial.available()<=0) {
      }
      if(Serial.available())
      {
          seg4 = Serial.parseFloat();
      }

  }
    
  


if(byteRead== 68) //D
{
seg1 = 1.1;
seg2 = 1.1;
seg3 = 1.1;
seg4 = 1.1;
}
  }
Current_Contorl[0] = seg1;
  Current_Contorl[1] = seg2;
  Current_Contorl[2] = seg3;
  Current_Contorl[3] = seg4;

dtostrf(Current_Contorl[0],4,3,t_Valve_State[0]);
dtostrf(Current_Contorl[1],4,3,t_Valve_State[1]);
dtostrf(Current_Contorl[2],4,3,t_Valve_State[2]);
dtostrf(Current_Contorl[3],4,3,t_Valve_State[3]);
Transmissiondata(SLAVE_ADDRESS1,t_Valve_State[0]);
Transmissiondata(SLAVE_ADDRESS2,t_Valve_State[1]); 
Transmissiondata(SLAVE_ADDRESS3,t_Valve_State[2]); 
Transmissiondata(SLAVE_ADDRESS4,t_Valve_State[3]); 

}

void Transmissiondata(byte SLAVE_ADDRESS,char array[])
{
  Wire.beginTransmission(SLAVE_ADDRESS);   
  Wire.write(array);         //left/right       
  //Wire.write();//pwm values
  Wire.endTransmission();
  
}

