
//This file initializes the variables which assign frequenceis to different notes
#include "pitches.h"

//Wire library for I2C
#include <Wire.h>

//File for Spark Fun MMA8452Q sensor
#include "SFE_MMA8452Q.h"
void printOrientation();

// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.
MMA8452Q accel;


#define FORCE_SENSOR_PIN A0

// mode controls the note that is to be played
int mode = 1;


//int noteDuration = 250;


// List of notes, the index value is maintained by 'mode' variable
int melody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
  };
  
void setup()
{
  Serial.begin(9600);

  //Initializes the acceleration functionality
  accel.init();
}

void loop()
{
  // First, use accel.read() to read the new variables:
  accel.read();
  printOrientation();

  // When instrument is flat, no note is played
  if (mode == 0)
  {
    return;     //Restarts the loop() function. [works like continue for a while or for loop]
  }

  // Takes reading from the force sensor and changes the mode of the instrument
  int analogReading = analogRead(FORCE_SENSOR_PIN);

  // Adding more divisions to the pressure level would allow freedom to add more sets of notes based on the pressure sensitivity
  if (analogReading < 700) // from 500 to 799
    { 
      Serial.print("No presure - first 4 notes :") ;
    }
  else
    {
      Serial.print("Presure - next 4 notes :") ;
      mode = mode + 4;    // Plays the next 4 notes in the same order. 
    }

  tone(8, melody[mode-1], 250); //Plays tone on pin8, at frequency melody[mode-1] for 250ms
  
  Serial.println(melody[mode-1]);   //Prints the frequency that is to be played
}


// function, which reads the portrait/landscape status of the sensor.
void printOrientation()
{
  // accel.readPL() will return a byte containing information about the orientation of the sensor. 
  // The different orientations are PORTRAIT_U, PORTRAIT_D, LANDSCAPE_R, LANDSCAPE_L, or LOCKOUT.
  byte pl = accel.readPL();
  
  switch (pl)
  {
    case PORTRAIT_U:
      Serial.print("Portrait Up ");
      mode = 4;
      break;
    case PORTRAIT_D:
      Serial.print("Portrait Down ");
      mode = 2;
      break;
    case LANDSCAPE_R:
      Serial.print("Landscape Right ");
      mode = 1;
      break;
    case LANDSCAPE_L:
      Serial.print("Landscape Left ");
      mode = 3;
      break;
    case LOCKOUT:
      Serial.print("Flat ");
      mode = 0;
      break;
  }
}
