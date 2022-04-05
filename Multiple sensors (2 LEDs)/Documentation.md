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
Next, 
