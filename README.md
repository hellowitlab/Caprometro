# Caprometro
Goat Meter from team Thorussel @ Witlab

This thing is used for printing on a lcd screen the scores of two different teams. It is provided with three different special buttons made of a conductive gel. The two with the goat shape are used for adding points with, a goat moan in the background and a goat made of wood glued to the servo motor will make you lough. The button in the middle, with an elephant on a sprng, is used for resetting the scores of the two teams.

# Required Equipment

-LCD screen.

-jump wires.

-bare conductive touchboard supplied with the micro SD(https://www.youtube.com/watch?v=dKFRweXei90).

-servo motor.

-speakers.

-power supply.

-welder.

-conductive gel.

-wood.

-laser cutter.

-nuts and bolts.

# Code

Before programming the touchboard you can use the Arduino IDLE but you need to install several stuff, see https://www.bareconductive.com/make/setting-up-arduino-with-your-touch-board/). They give you some examples too.





// touch includes
#include <MPR121.h>
#define MPR121_ADDR 0x5C
#include <Wire.h>
// mp3 includes
#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h> 
#include <SFEMP3Shield.h>
// mp3 variables
SFEMP3Shield MP3player;
byte result;
//lcd includes and variables
#include <LiquidCrystal.h>
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);
//servo includes and variables
Servo servo;
#include <Servo.h>
// sd card instantiation
SdFat sd;
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
      if(MPR121.isNewTouch(1)){//button one pressed
        wind++;
        servo.attach(10);
        servo.write(200);
        delay(800);
        servo.write(5);
        delay(200);
        servo.detach();
        MP3player.playTrack(0);     
     }  
      else if(MPR121.isNewTouch(10)){//button ten pressed
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
      else if(MPR121.isNewTouch(3)){//button three pressed
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

# Build it!

The bare conductive touchboard with his ELECTRODE SOLDER PADS  gives you a great and creative way of creating things with sounds or with the use of the conductive jel.

We firstly tryed it with an Arduino and a bread board and than we added sounds and touch buttons so we had to use another type of board for the final project.