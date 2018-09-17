#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Wire.h>
//Beginning of Auto generated function prototypes by Atmel Studio
//void receiveEvent(int bytes);
//End of Auto generated function prototypes by Atmel Studio

int PWML = 5;
int PWMR = 6;
int LED_VALVE = 11;

//#define SLAVE_ADDRESS 0x67 //Segment 1
//#define SLAVE_ADDRESS 0x68 //Segment 2
//#define SLAVE_ADDRESS 0x69 //Segment 3
//#define SLAVE_ADDRESS 0x70 //Segment 4
//#define SLAVE_ADDRESS 0x71 //Segment 5
//#define SLAVE_ADDRESS 0x72 //Segment 6
byte byteRead;
int seg1 = 0;
char t[7];
char ratio[7]={};
void setup()
{
	//Wire.begin();
	Serial.begin(9600);
	//Wire.begin(SLAVE_ADDRESS);
	//Wire.onReceive(receiveEvent);
	pinMode(PWML,OUTPUT);
	pinMode(PWMR,OUTPUT);
	pinMode(LED_VALVE,OUTPUT);
	TCCR0B = (TCCR0B & 0b11111000) | 0x05;

}

void loop()
{
	if (Serial.available()){
		Serial.println("in the loop");
		byteRead = Serial.read();
		if(byteRead== 83) //S
		{
			//  delay(200);
			digitalWrite(PWML,LOW);
			digitalWrite(PWMR,LOW);
			Serial.println("stop");
			digitalWrite(LED_VALVE,LOW);

		}
		if(byteRead== 65) //A
		{
			Serial.println("Input left:");
			while(1) {
				//Serial.println("LOOP A");
				if(Serial.available())
				{
					seg1 = Serial.parseInt();
					Serial.print("left:");
					Serial.println(seg1);
					//delay(100);
					break;
				}
			}

			analogWrite(PWML,seg1);
			analogWrite(PWMR,0);
			digitalWrite(LED_VALVE,HIGH);
		}


		if(byteRead== 68) //D
		{
			Serial.println("Input right:");
			while(1) {
				// Serial.println("LOOP D");
				if(Serial.available())
				{
					seg1 = Serial.parseInt();
					Serial.print("right:");
					Serial.println(seg1);
					// delay(100);
					break;
					// }
				}
			}
			
			analogWrite(PWML,0);
			analogWrite(PWMR,seg1);
			digitalWrite(LED_VALVE,HIGH);

		}


	}
}



/*void receiveEvent(int bytes)
{
	int i=0;
	while (Wire.available()) { // loop through all but the last
		ratio[i] = Wire.read(); // receive byte as a character
		i=i+1;
	}
	
	float Ratio = atof(ratio);
	Serial.println(ratio);
	if (Ratio>0 && Ratio<0.8)	
	{
		digitalWrite(PWML,LOW);
		digitalWrite(PWMR,HIGH);
	}
	if (Ratio<0)
	{
		digitalWrite(PWML,HIGH);
		digitalWrite(PWMR,LOW);
	}
	if (Ratio>0.8)	
	{
		digitalWrite(PWML,LOW);
		digitalWrite(PWMR,LOW);
	}
}*/

