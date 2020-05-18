#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX 
DFRobotDFPlayerMini myDFPlayer;  //Instantiate myDFPlayer 
int maxSongs = 0;  //How many songs are on the SD card?
long currentSong=0;
int A0Value;
unsigned long newSeed;
unsigned long pinZeroValue;
unsigned long playingStart;
unsigned long playingTotal;
int play_state;
//
// Most displays are at address 0x27, but some are 0x35; use the SCANNER program 
// available at some Arduino sites to see which you have, or if 0x27 fails,
// try 0x35.
//


void setup()
{
mySoftwareSerial.begin(9600);  //Start serial communication
Serial.print("newSeed=");Serial.print(newSeed);  Serial.print("   A0Value=");Serial.println(A0Value); 
Serial.begin(9600); 
Serial.println("DFRobot DFPlayer Mini");
Serial.println("Initializing DFPlayer... (please wait 3~5 seconds)");
if (!myDFPlayer.begin(mySoftwareSerial))
{
Serial.println("Initialization Failure:");
Serial.println("1.Check the connections to the DFPlayer Mini");
Serial.println("2.Make certain the SD card is inserted in the player");
while (true);
}

Serial.println();
Serial.println("DFPlayer Mini Module initialized!");
delay(1000);
A0Value=analogRead(0);
//newSeed=millis()*A0Value;
newSeed=A0Value-440;
randomSeed(newSeed);
Serial.print("newSeed=");Serial.print(newSeed);  Serial.print("   A0Value=");Serial.println(A0Value);  

//Initialize Player Parameters
myDFPlayer.setTimeOut(500); //Timeout serial 500ms
myDFPlayer.volume(15); // Max Volume is 30     
myDFPlayer.EQ(0); //Normal Equalization
maxSongs = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD);
Serial.println();
Serial.print("Number of sound files on SD card: "); Serial.println(maxSongs);
}

void loop()
{
             
          currentSong=random(0,maxSongs)+1;  //Generate a random number of a song to play
          Serial.print("Now Playing: "); Serial.println(currentSong);
          myDFPlayer.play(currentSong);      //Start playing the random song
          playingStart=millis();
          delay(250);
          boolean play_state=digitalRead(8);  //pin the playing state to see if we are playing a song right now
          //
          while (play_state==0)
             {
              //
              //
              delay(5000);
              playingTotal=(millis()-playingStart)/1000; 
              Serial.print("Current song playing time = ");Serial.print(playingTotal);Serial.println(" seconds."); 
              play_state=digitalRead(8);
              //
              //  If playing state goes to 1, we have come to the end of a song, 
              //
           }  //end of if(play_state==0)

     

     delay(1000);
} //  end of main loop
