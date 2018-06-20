#include <MPR121.h>
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include <SdFat.h>
#include <FreeStack.h> 
#include <SFEMP3Shield.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); 
Servo servo;
SFEMP3Shield MP3player;
SdFat sd;
byte result;
#define MPR121_ADDR 0x5C
void setup(){
  lcd.begin(16,2);
  servo.write(5);
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
   
  Wire.begin();
  
  MPR121.setInterruptPin(4);
  
  MPR121.setTouchThreshold(40);     
       
  MPR121.setReleaseThreshold(20);   
                                    
  result = MP3player.begin();
  
  MP3player.setVolume(10,10);
  
  MPR121.updateTouchData();
}

int wind=0;
int rain=0;

void loop(){
  if(MPR121.touchStatusChanged()){
      MPR121.updateTouchData();
      if(MPR121.isNewTouch(1)){
        wind++;
        servo.attach(10);
        servo.write(200);
        delay(800);
        servo.write(5);
        delay(200);
        servo.detach();
        MP3player.playTrack(0);     
     }  
      else if(MPR121.isNewTouch(10)){
        rain++;
        servo.attach(10);
        servo.write(200);
        delay(800);
        servo.write(5);
        delay(200);
        servo.detach();
        MP3player.playTrack(0);
     }
  }
      else if(MPR121.isNewTouch(3)){
        rain=0;
        wind=0;
        MP3player.playTrack(3);
    }
  
  lcd.clear();
  lcd.print("Wind=");
  lcd.setCursor(5,0);
  lcd.print(wind);
  lcd.setCursor(0,1);
  lcd.print("Rain=");
  lcd.setCursor(5,1);
  lcd.print(rain);
  delay(300);
}
