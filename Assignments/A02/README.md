# LED Intro

The following is where I am getting comfortable with the arduino. Here I will go over different mini projects that I tested to get introduced to the basics.

## Single LED Light up
##### Here I will make a RGB LED light up using Arduino IDE

![image](https://github.com/FatimaMarq14/4443-IoT/blob/main/Assignments/A02/Intro%20LED.jpg)



### Connection Schematic
![image](https://github.com/FatimaMarq14/4443-IoT/blob/main/Assignments/A02/Screenshot%202025-07-09%20224117.png)

A connection schematic, also known as a wiring diagram, is a visual representation of how electrical components are physically connected in a circuit. Here I used:
- (1) x Elegoo Uno R3
- (1) x 830 Tie Points Breadboard
- (4) x M-M wires (Male to Male jumper wires)
- (1) x RGB LED
- (3) x 220 ohm resistors

Inside a RGB are actually 3 LEDS that includes:
- 1 red
- 1 green
- 1 blue


The LED is able to "mix" colors by adjusting the brightness of each individual LED. <br/>
An RGB LED has four leads. Blue, Green, Cathode, and Red. Each LED requires a 220 ohm resistor to prevent too much current flowing through it.<br/>

### How It Works:
- Common anode means you connect the longest leg to **5V**
- To turn a color **ON**, you write `LOW` to that pin
- This sketch turns only the BLUE LED on

### Arduino Code:
```cpp
#define RED 6
#define GREEN 5
#define BLUE 3

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, LOW);    // Turn RED OFF
  digitalWrite(GREEN, LOW); // Turn GREEN OFF
  digitalWrite(BLUE, HIGH);  // Turn BLUE ON
}
```
## Delay Single LED Light up

Next I decided to find how I can change the colors and implemented the **delay** command. <br/> The following code is similar to the top code; however, this time we are including a delay for Red, Green, and Blue. 
```cpp
#define RED 6
#define GREEN 5
#define BLUE 3

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // Turn on RED only
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  delay(1000); // Wait 1 second

  // Turn on GREEN only
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
  delay(1000); // Wait 1 second

  // Turn on BLUE only
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, LOW);
  delay(1000); // Wait 1 second
}
```

## Potentiometer 10k

Finally, I added the potentiometer to the project to test out its functions. This required minimal addition to the arduino and a couple of changes to the code. <br/>

![image](https://github.com/FatimaMarq14/4443-IoT/blob/main/Assignments/A02/Delay%20LED.jpg)


A potentiometer was connected to analog input A0. The other two pins are connected to 5v and GND. Its value is read as analog inout **potValue** where it ranges from 0 to 1023. This allows the range to be divided into 3 segments:
1. 0 to 340
   - The RED LED brightness changes smoothly from dim (0) to bright (255) as the potentiometer is turned.
   - GREEN and BLUE LEDs are set fully bright (255) to create a dimmer effect on red.
2. 341 to 681:
   - The GREEN LED brightness changes smoothly from dim (0) to bright (255) based on the potentiometer position.
   - RED and BLUE LEDs are set fully bright (255).
3. 682 to 1023:
   - The BLUE LED brightness changes smoothly from dim (0) to bright (255).
   - RED and GREEN LEDs are set fully bright (255).

I then discovered other functions that are needed in order for the potentiometer to work properly. 

**pinMode()** sets LED pins as outputs.

**analogRead(POT)** reads the potentiometer position.

**analogWrite()** controls the LED brightness using PWM.

**map()** converts the potentiometer value range into PWM brightness values for fading.



```cpp
#define RED 6
#define GREEN 5
#define BLUE 3
#define POT A0

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  int potValue = analogRead(POT);  // 0-1023

  // Map potValue into three segments for colors:
  if (potValue < 341) {
    // RED on, others off
    analogWrite(RED, map(potValue, 0, 340, 0, 255));       // Fade RED from bright to dim
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 255);
  } else if (potValue < 682) {
    // GREEN on
    analogWrite(RED, 255);
    analogWrite(GREEN, map(potValue, 341, 681, 0, 255));    // Fade GREEN from bright to dim
    analogWrite(BLUE, 255);
  } else {
    // BLUE on
    analogWrite(RED, 255);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, map(potValue, 682, 1023, 0, 255));    // Fade BLUE from bright to dim
  }
}
```
