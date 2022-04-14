Link to video]()

For this musical instrument assignment, we wanted to explore different and unique types of sensors we haven't seen in class yet. We looked around in the IM Lab and thought of all the different ways we could use the sensors available to us. Some of our options were:
- infrared sensor
- photoresistor 
- motion sensor
- force resistor
- accelerometer

We ended up using an accelerometer as our primary sensor. 

Next, we had to figure out how we were going to wire up the accelerometer and what code could we potentially use. After thorough research trying to find the type of accelerometer we had and trying to find the wiring/code for it, we decided to use the orientation function of the accelerometer for our instrument. 

Some of the websites that were really helpful during this process:

[To understand how the accelerometer works](https://lastminuteengineers.com/adxl335-accelerometer-arduino-tutorial/)

[For the code/wiring](https://forum.arduino.cc/t/mma8452-accelerometer-not-working-arduino-uno-cheese-cake-for-the-best-answer/493668)

*insert mathematical explanation for how we used the accelerometer*

*pic of accelerometer wiring*
*pic of accelerometer code*

Then, we wanted to add another sensor that could have other functions than the accelerometer and give us access to more notes, but that we could also use simultaneously with the accelerometer. That’s when we decided that a force sensor would be perfect for this job.

We wired up the force sensor and found a code that would help us integrate it in our circuit:

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

We ended up removing all the different options of ‘squeezes’ and only keeping one. That way, there were only two possible inputs: squeeze or no squeeze.

After that, we connected the piezo buzzer alone and wanted to test out a few things with it, like its volume and the melodies it can play, before adding it to the accelerometer circuit.

*insert pic of circuit without potentiometer*


We tested out the melody using tone() function code that we did in class and ended up using the library used there in our final code:
https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody

We used the ‘pitches.h’ library to access different music notes.

However, we realized that the buzzer volume was too low, so we tested out many different codes to try to make the volume higher.

We tried out codes like:
https://create.arduino.cc/projecthub/connornishijima/tone-with-8-bit-volume-control-no-extra-components-370c66

https://create.arduino.cc/projecthub/glennedi/dc-piezo-buzzer-volume-control-4a230b



*insert pic of us trying codes*


After many attempts, we ended up using a potentiometer (no code needed) to control the volume of the piezo buzzer.

Finally, we added a switch (no code, circuit in series), and put all the bits of code together in one and tested it all out.

Future improvements:
- Adding more force sensors and creating an array of different notes
- Using an LCD screen to display which notes are playing
-Creating a hand glove or a type of asing to facilitate playing the instrument

