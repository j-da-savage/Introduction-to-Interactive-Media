[Link to video](https://drive.google.com/file/d/18_NgovwbAKv7W_LThACd1o48hPwp8XBT/view?usp=sharing)

For this musical instrument assignment, we wanted to explore different and unique types of sensors we haven't seen in class yet. We looked around in the IM Lab and thought of all the different ways we could use the sensors available to us. Some of our options were:
- infrared sensor
- photoresistor 
- motion sensor
- force resistor
- accelerometer

We ended up using an accelerometer as our primary sensor, because of the freedom of motion it would allow us.

Next, we had to figure out how we were going to wire up the accelerometer and what code could we potentially use. After thorough research trying to find the type of accelerometer we had and trying to find the wiring/code for it, we decided to use the orientation function of the accelerometer for our instrument. 

Some of the websites that were really helpful during this process:

[To understand how the accelerometer works](https://lastminuteengineers.com/adxl335-accelerometer-arduino-tutorial/)

[For the code/wiring](https://forum.arduino.cc/t/mma8452-accelerometer-not-working-arduino-uno-cheese-cake-for-the-best-answer/493668)

The accelerometer works by measuring the static or dynamic forces acting on the body using a sensor. The values that show up while our instrument was still were measurements of the static force of gravity. When we picked up the instrument, the values showed significant changes due to the dynamic force caused by motion. These forces along the X, Y and Z axes can be analyzed and the orientation of the device can be calculated. We used this orientation value for our instrument.

![pic of accelerometer wiring](https://github.com/j-da-savage/Introduction-to-Interactive-Media/blob/main/Musical%20Instrument/testing%20wiring%20for%20accelerometer.jpg)
![pic of accelerometer code](https://github.com/j-da-savage/Introduction-to-Interactive-Media/blob/main/Musical%20Instrument/accelerometer%20code%20working.jpg)

Then, we wanted to add another sensor that could have other functions than the accelerometer and give us access to more notes, but that we could also use simultaneously with the accelerometer. That’s when we decided that a force sensor would be perfect for this job.

We wired up the force sensor and found a code that would help us integrate it in our circuit:


```
#define FORCE_SENSOR_PIN A0 // the FSR and 10K pulldown are connected to A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogReading = analogRead(FORCE_SENSOR_PIN);

  Serial.print("Force sensor reading = ");
  Serial.print(analogReading); // print the raw analog reading

  if (analogReading < 10)       // from 0 to 9
    Serial.println(" -> no pressure");
  else if (analogReading < 200) // from 10 to 199
    Serial.println(" -> light touch");
  else if (analogReading < 500) // from 200 to 499
    Serial.println(" -> light squeeze");
  else if (analogReading < 800) // from 500 to 799
    Serial.println(" -> medium squeeze");
  else // from 800 to 1023
    Serial.println(" -> big squeeze");

  delay(1000);
}
```

We ended up removing all the different options of ‘squeezes’ and only keeping one. That way, there were only two possible inputs: squeeze or no squeeze.

After that, we connected the piezo buzzer alone and wanted to test out a few things with it, like its volume and the melodies it can play, before adding it to the accelerometer circuit.

![insert pic of circuit without potentiometer](https://github.com/j-da-savage/Introduction-to-Interactive-Media/blob/main/Musical%20Instrument/circuit%20without%20potentiometer%20and%20switch.jpg)


We tested out the melody using tone() function code that we did in class and ended up using the library used there in our final code:
https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody

We used the ‘pitches.h’ library to access different music notes.

However, we realized that the buzzer volume was too low, so we tested out many different codes to try to make the volume higher.

We tried out codes like:
https://create.arduino.cc/projecthub/connornishijima/tone-with-8-bit-volume-control-no-extra-components-370c66

https://create.arduino.cc/projecthub/glennedi/dc-piezo-buzzer-volume-control-4a230b

![speaker trying](https://github.com/j-da-savage/Introduction-to-Interactive-Media/blob/main/Musical%20Instrument/testing%20out%20volume%20code%20with%20a%20speaker.jpg)


After some attempts, we ended up using a potentiometer (no code needed) to control the volume of the piezo buzzer.

Finally, we added a switch (no code, circuit in series), and put all the bits of code together in one and tested it all out.

Future Improvements:
  - Our instrument leaves scope for a lot of improvements due to the fact that we used an accelerometer. THis gives us access to 3 dimensions which will allow us to change pitch, scale, octaves and even different instruments!
  - Adding more force sensors and developing on that could lead to a 3 dimensional portable piano. This could be fit on a glove to make it a well finished product.
  - We could also add an LCD screen to the breadboard to let the user know what note they are playing. THis could especially be helpful after making the above improvements since it will allow for more possibilities.

Final Code:
```

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
```
