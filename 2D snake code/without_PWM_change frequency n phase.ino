

#include <Wire.h>
// Locomotion
float t;
const float pi = 3.14;
int N = 4;
float w = 4*pi;
float w_print = 4;
float phio = 0;
double ta = 1*pi/2;
double ta_print = 90;
//double ta_print_f = 0;
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
    
    if(byteRead== 65) //A
      {
        tragger = 0;
     float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
     float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
          ta = 1*pi/2;
          w = 4*pi;
          ta_print = 90;
          w_print = 4;
          phio = phio - 0.05;
          digitalWrite(STBY, LOW);
      }
    
    if (byteRead == 68) // D
    {
      tragger = 0;
    float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
    float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
        ta = 1*pi/2;
        ta_print = 90;
        w = 4*pi;
        w_print = 4;
        phio = phio + 0.05;
        digitalWrite(STBY, LOW);
    }
    
    if (byteRead == 87) //W
    {
      tragger = 0;
    float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
    float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
        ta = 1*pi/2;
        w = 4*pi;
        ta_print = 90;
        w_print = 4;
        phio = 0;
        //ta_print_f = ta_print*180;
        Serial.println(w_print);
        Serial.println(ta);
        Serial.println(ta_print);
        digitalWrite(STBY, LOW);
    }        
    
    if (byteRead == 90) //Z, reduce frequency by 0.5pi
    {
        //w = w - 0.5*pi;
        w_print = w_print - 0.5;   
        w = w_print * pi;
        tragger = 0;
        float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
        float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
    
        phio = 0;
        //ta_print_f = ta_print * 180;       
        Serial.println(w_print);
        Serial.println(ta);
        Serial.println(ta_print);
        digitalWrite(STBY, LOW);
    }

    if (byteRead == 88) //X, increase frequency by 0.5 pi
    {
        //w = w + 0.5*pi;
        w_print = w_print + 0.5;   
        w = w_print * pi;
        tragger = 0;
        float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
        float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
    
        phio = 0;  
        //ta_print_f = ta_print * 180;
        Serial.println(w_print);
        Serial.println(ta);
        Serial.println(ta_print);
        digitalWrite(STBY, LOW);
    }
    
    if (byteRead == 78) // N, reduce ta for 1/12 pi
    {
      tragger = 0;
        float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
        float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
        phio = 0;
        ta = ta - 1*pi/12;
        ta_print = ta_print - 15;
        //ta = ta_print * pi;
        //ta_print_f = ta_print * 180;
        Serial.print(w_print);
        Serial.println(ta);
        Serial.println(ta_print);
        digitalWrite(STBY, LOW);
    }

        if (byteRead == 77) // M, increase ta for 1/12 pi
    {
      tragger = 0;
        float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
        float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
        phio = 0;
        ta = ta + 1*pi/12;
        ta_print = ta_print + 15;
        //ta = ta_print * pi;
        //ta_print_f = ta_print * 180;
        Serial.println(w/pi);
        Serial.println(ta);
        Serial.println(ta_print);
        digitalWrite(STBY, LOW);
    }

    if(byteRead == 74)// J
    {
     Serial.println("Input frequency");
    //delay(50);
     while(Serial.available()<=0) {
      //Serial.println("Hello");
      //delay(50);
      }
      if(Serial.available())
      {
          w = Serial.parseFloat()*pi;
      }
      Serial.println("Input phase");
      //delay(50);
      while(Serial.available()<=0){
        //Serial.println("World");
        //delay(50);
        }
      if(Serial.available())
      {
          ta = Serial.parseFloat()/180.0*pi;
      }
       Serial.println(w);
       Serial.println(ta); 
       tragger = 0;
       float Current_Control_Max[4] = {0.7,0.7,0.7,0.7};
       float Current_Control_Min[4] = {-0.7,-0.7,-0.7,-0.7};
       
       phio = 0;

      }

    
    if (byteRead == 83) //S
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
        if (byteRead == 81) //Q
    {
     tragger = 1;
    phio = 0;
    
    digitalWrite(STBY, HIGH); //disable standby
    int j = 1;
    analogWrite(PWMA, 255);
    }
    if (byteRead == 80) //P
    {
     tragger = 1;
     phio = 0;
     ta = 1*pi/2;
     ta_print = 90;
     w = 4*pi;
     w_print = 4;
     Serial.println(w_print);
     Serial.println(ta);
     Serial.println(ta_print);
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


