#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX 
DFRobotDFPlayerMini myDFPlayer;  //Instantiate myDFPlayer 
 
// Arduino stepper motor control code

#include <Stepper.h> // Include the header file

LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,20,4);

// change this to the number of steps on your motor
#define STEPS 128

// create an instance of the stepper class using the steps and pins
Stepper stepperChopper(STEPS, 2,4,3,5);  //Yes, I know these numbers are out of order.
Stepper stepperTree(64, 6,8,7,9);        //They need to be out of order to properly
                                         //phase shift the four coils of a stepper motor.
int val = 550;
int chops;
int cycle;
int startflag=HIGH;
int moveChopperLeft;
int moveChopperRight;
int moveTreeLeft;
int moveTreeRight;
unsigned long int laststarttime;

void setup() 
{
pinMode(12,INPUT_PULLUP);
pinMode(14,INPUT_PULLUP);
pinMode(15,INPUT_PULLUP);
pinMode(16,INPUT_PULLUP);
pinMode(17,INPUT_PULLUP);
delay(250); 


lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Lumberjack Paused   ");
lcd.setCursor(1,1);
lcd.print("                    ");
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);  //Start serial communication

  mySoftwareSerial.println("In SETUP");
  stepperChopper.setSpeed(256);
  stepperTree.setSpeed(150);
  
//Initialize Player Parameters
myDFPlayer.setTimeOut(500); //Timeout serial 500ms
delay(500);
if (!myDFPlayer.begin(mySoftwareSerial))
      {
      Serial.println("Initialization Failure:");
      Serial.println("1.Check the connections to the DFPlayer Mini");
      Serial.println("2.Make certain the SD card is inserted in the player");
      lcd.setCursor(0,1);
      lcd.print("Audio Init Failure  ");
      }
      else
      {
      lcd.setCursor(0,1); 
      lcd.print("Audio Init Success  ");
      }
myDFPlayer.volume(30); // Max Volume is 30     
myDFPlayer.EQ(0); //Normal Equalization
}

void loop() 
{
  if(cycle==0)
  {
  moveChopperLeft=analogRead(0);
  moveChopperRight=analogRead(1);
  moveTreeLeft=analogRead(2);
  moveTreeRight=analogRead(3);
  /*
  Serial.print ("Pin A0, A1, A2, A3 = ");
     Serial.print(moveChopperLeft); Serial.print("  ");
     Serial.print(moveChopperRight); Serial.print("  ");
     Serial.print(moveTreeLeft);Serial.print("  ");
     Serial.println(moveTreeRight);
   delay(1000);
   */
   if(moveChopperLeft<950)
      {
        stepperChopper.step(-20);
        Serial.println("Moving Chopper to the Left");
        delay(250);
      }
   if(moveChopperRight<950)
      {
        stepperChopper.step(20);
        Serial.println("Moving Chopper to the Right");
        delay(250);
      }
   if(moveTreeLeft<950)
      {
        stepperTree.step(-25);
        Serial.println("Moving Tree to the Left");
        delay(250);
      }
   if(moveTreeRight<950)
      {
        stepperTree.step(25);
        Serial.println("Moving Tree to the Right");
        delay(250);
      }
  }
  startflag=digitalRead(12);
  delay(200);
  //Serial.print("startflag = ");Serial.println(startflag);
  if(startflag==LOW)
    {
    cycle=cycle+1;
    Serial.print("Lumberjack Chopping, cycle = ");Serial.println(cycle);
    lcd.setCursor(0,0);
    lcd.print("Lumberjack Chopping ");  
    lcd.setCursor(0,1);
    lcd.print("                    ");  
    
    for (chops = 1; chops <= 5; chops++) 
       {       
       myDFPlayer.play(2); //single chop
       stepperChopper.step(-val);
       delay(100);
       stepperChopper.step(val); 
       delay(350);
       }
       
    myDFPlayer.play(3); //falling tree

    Serial.println("  Tree is Falling");
    lcd.setCursor(0,0);
    lcd.print("Lumberjack Treefall ");
    
    stepperTree.setSpeed(30);  //Speed will accelerate during the fall
    stepperTree.step(-50);     //total movement should be about 435 steps
    delay(10);  
    
    stepperTree.setSpeed(50);  
    stepperTree.step(-75);
    delay(10); 
    
    stepperTree.setSpeed(70);  
    stepperTree.step(-110);
    delay(10);
    
    stepperTree.setSpeed(127);
    stepperTree.step(-200);
    delay(10);
    
    stepperTree.setSpeed(100);
    stepperTree.step(60);
    
    stepperTree.setSpeed(60);  //Bounce up
    stepperTree.step(30);
    delay(100);
    
    stepperTree.step(-30);
    
    stepperTree.setSpeed(100); //Bounce Down
    stepperTree.step(-60);
    delay(5000);
    stepperTree.setSpeed(127);
    stepperTree.step(435);
    delay(4500);
    startflag=0;
    lcd.setCursor(0,0);
    lcd.print("Lumberjack Paused   ");
    Serial.println("  Action is completed");
   }
}
