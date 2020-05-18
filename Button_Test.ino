#include "SoftwareSerial.h"
int startflag;
void setup() 
{  
  Serial.begin(9600);
  digitalWrite(12,LOW);
  pinMode(12,INPUT_PULLUP);
  delay(500);
}


void loop() 
  {
  startflag=digitalRead(12);
  if(startflag==HIGH)
      {
      Serial.println("startflag is HIGH");
      }
  if(startflag==LOW)
      {
      Serial.println("startflag is LOW");
      }
  delay(3000);
  }
