

#include <Wire.h>
// Locomotion
float t;
const float pi = 3.14;
int N = 4;
int w = 4*pi;
float phio = 0;
int ta = 3*pi/4;
float Valve_State[4];
float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
char t_Valve_State[4][7];
int STBY = 7; //standby
//Motor A
int PWMA = 6; //Speed control 
int AIN1 = 8; //Direction
int AIN2 = 9; //Direction
int tragger = 0;
//I2C
#define SLAVE_ADDRESS1 0x67
#define SLAVE_ADDRESS2 0x68
#define SLAVE_ADDRESS3 0x69
#define SLAVE_ADDRESS4 0x70




//Interrupt



byte byteRead;
void setup()
{
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  Wire.begin(); 
  Wire.setClock(100000);
  Serial.begin(9600);    
}


void loop()
{
    
    
  float Time = millis();
  t = Time/1000.000;
  
  if (Serial.available()) {
    
    byteRead = Serial.read();
    
    if(byteRead== 65)
      {
        tragger = 0;
     float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
     float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
          phio = phio - 0.05;
          digitalWrite(STBY, LOW);
      }
    if (byteRead == 68)
    {
      tragger = 0;
    float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
    float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
        phio = phio + 0.05;
        digitalWrite(STBY, LOW);
    }
    if (byteRead == 87)
    {
      tragger = 0;
    float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
    float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
        phio = 0;
        digitalWrite(STBY, LOW);
    }
    if (byteRead == 83)
    {
      tragger = 0;
   float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
   float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
        phio = 0;
    digitalWrite(STBY, HIGH); //disable standby
    analogWrite(PWMA, 255);   
    }
    if (byteRead == 69)
    {
     tragger = 1;
    phio = 0;
    digitalWrite(STBY, HIGH); //disable standby
    int j = 1;
    analogWrite(PWMA, 255);
    delay(10);
    analogWrite(PWMA, 0);
    }
        if (byteRead == 81)
    {
     tragger = 1;
    phio = 0;
    digitalWrite(STBY, HIGH); //disable standby
    int j = 1;
    analogWrite(PWMA, 255);
    }
    if (phio > 0.5)
    {
        phio = 0.5;
    }
     if (phio < -0.5)
    {
        phio = -0.5;
    }
    }
 if (tragger == 1)
 {
  for (int i = 0; i < N; i++)
  {
            if (sin(w*t+ta*i)+phio < 0)
                     {
                           Valve_State[i] = 0.9;
                     }
            else
                     {
                           Valve_State[i] = 0.9;
                     }
  } 
 }
  if (tragger == 0)
 {
  for (int i = 0; i < N; i++)
  {
            if (sin(w*t+ta*i)+phio < 0)
                     {
                           Valve_State[i] = Current_Control_Max[i];
                     }
            else
                     {
                           Valve_State[i] = Current_Control_Min[i];
                     }
  } 
 }
// 
dtostrf(Valve_State[0],4,3,t_Valve_State[0]);
dtostrf(Valve_State[1],4,3,t_Valve_State[1]);
dtostrf(Valve_State[2],4,3,t_Valve_State[2]);
dtostrf(Valve_State[3],4,3,t_Valve_State[3]);
Transmissiondata(SLAVE_ADDRESS1,t_Valve_State[0]);
Transmissiondata(SLAVE_ADDRESS2,t_Valve_State[1]); 
Transmissiondata(SLAVE_ADDRESS3,t_Valve_State[2]); 
Transmissiondata(SLAVE_ADDRESS4,t_Valve_State[3]); 
}    

void Transmissiondata(byte SLAVE_ADDRESS,char array[])
{
  Wire.beginTransmission(SLAVE_ADDRESS);   
  Wire.write(array);                
  Wire.endTransmission();
}


