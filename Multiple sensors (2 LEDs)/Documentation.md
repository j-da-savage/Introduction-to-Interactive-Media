[Link to the Video](https://youtube.com/shorts/O4PeQUqb0qA)

With this assignment, I personally felt a bit limited in terms of the cicuit I was going to create, especially since I only had a photoresistor as my analog input source. So, I wanted to be as creative as possible and put my circuit to good use and make it useful.

To gain a better understanding of the circuits previously done in class, I first recreated the photoresistor circuit with one LED. I also wanted to test out a possible digital input by using the same method of the aluminium switch from my last homework:

![Circuit 1](https://github.com/j-da-savage/Introduction-to-Interactive-Media/blob/main/Multiple%20sensors%20(2%20LEDs)/attempt%20at%20photoresistor%20circuit%20.png)

I used the following code for it (same code done in class):

```
const int LED_PIN = 3;
const int POT_PIN = A1;

int value = 0;
int potValue = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  potValue = analogRead(POT_PIN);
  Serial.println(potValue);
  int ledValue = 255- potValue/4;
  analogWrite(LED_PIN, ledValue);
}
```
Next, I tested out my circuit with a button, but the LED did not seem to turn on, and on top of that, the circuit was not reading any values from the photoresistor anymore.

![Circuit 2](https://github.com/j-da-savage/Introduction-to-Interactive-Media/blob/main/Multiple%20sensors%20(2%20LEDs)/attempt%20at%20button%20.png)

The code I used for that was the same as the previous one but with the addition of the code for the button:

![struggle](https://github.com/j-da-savage/Introduction-to-Interactive-Media/blob/main/Multiple%20sensors%20(2%20LEDs)/attempt%20at%20code.png)

That's when I decided to use a switch instead of a button, in order to keep the mode "ON". I used the following code for it, with the addition of the photoresistor code:

```
// about this circuit
// LED in connected to PIN 7 -> controlled by digitalWrite
// SWITCH is connected to PIN 3 -> controlled by digitalRead

const int LED_PIN = 7;
const int SWITCH_PIN = 3;
int state = 0; //initialise the state variable to 0

void setup() {
  // set up the pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {

  int buttonValue = digitalRead(SWITCH_PIN);
  
  if(buttonValue == HIGH) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
}
```
At this stage, the switch was also working, but there was still no inout being recieved by the photoresistor. I then did some research and looked at previous examples from class, and then realized that if I wanted the switch and photoresistor to work simultaneously (aka: digitalWrite + analogWrite), I needed to use an if-statement where one of the conditions would use digitalWrite (when switch is off), and the other would use analogWrite (when the switch is on). I made these changes and it worked!

I then added an LED that would be controlled using only digitalWrite (so ON or OFF), and added the code for it in the if-statement.

![added LED](https://github.com/j-da-savage/Introduction-to-Interactive-Media/blob/main/Multiple%20sensors%20(2%20LEDs)/attempt%20at%20switch.png)

Finally, I connected the aluminum pieces to the pages of my book, and made sure they turned on and off the green LED (as I was doing continuously at every step). I fixed my code 
