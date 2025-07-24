# Soldering a Sonic LED Level Meter
The following is documentation on my process of creating a sonic LED Level Meter.

## Projects: LED Level Meter
<img src = "https://images2.imgbox.com/fc/8f/KC7Wtp0I_o.gif" width = "400">

### Componets I used:
- (1) x Ultrasonic Distance Sensor
- (1) x Breadboard
- (1) x Arduino Uno
- (1) x Printed Circuit Board
- (2) x Green LED
- (2) x Yellow LED
- (2) x Red LED
- (6) x 220 Resistors
- (11) x Male to Male Wires

### Ultrasonic Distance Sensor
*image of sensor here

The Ultrasonic sensor is a distance sensor that emits a high-frequency pulse that humans are not able to hear. It then waits to receive the echo with the sound bounces off from an object. It then calculates the distance based on time. 

### Pin Overview
The Ultrasonic sensor has 4 pins
- VCC
- Trig
- Echo
- Gnd
*image of pins here
#### VCC 
VCC is the power supply of the sensor. It requires a 5V where you connect it to the Vin of the arduino. 
#### TRIG
TRIG is an input pin that tells the sensor to "fire" a pulse. This is what is able to start the ultrasonic burst.
```cpp
const int trigPin = 11;   // TRIG pin of HC-SR04
.
.
// Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
```
#### ECHO
ECHO is the output pin where it reports how long the echo took. It Outputs a pulse and then gathers the distance (in this case centimeters).
```cpp
const int echoPin = 12;   // ECHO pin of HC-SR04
.
  long duration;
  float distance_cm;
.
.
  duration = pulseIn(echoPin, HIGH);
  distance_cm = (duration * 0.0343) / 2;
```
We use 0.034 because sound travels .034 cm per µs and divide it by 2 since sound goes there and back. 

#### GND 
GND is our ground 0V

### Arduino Code
The following is the code I used to be able to get the Sonic Sensor working. The code also includes information on where the pins should connect from the breadboard to the arduino. 
```cpp
// Ultrasonic Distance Measurement with HC-SR04

const int trigPin = 11; // TRIG pin of HC-SR04
const int echoPin = 12; // ECHO pin of HC-SR04

const int green1 = 2; 
const int green2 = 3;
const int yellow1 = 4;
const int yellow2 = 5;
const int red1 = 6;
const int red2 = 7;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set all LED pins as OUTPUT
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  long duration;
  float distance_cm;

  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance_cm = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Turn off all LEDs initially
  for (int i = 2; i <= 7; i++) {
    digitalWrite(i, LOW);
  }

  // Light up LEDs depending on the distance
  if (distance_cm < 10) digitalWrite(green1, HIGH);
  if (distance_cm < 20) digitalWrite(green2, HIGH);
  if (distance_cm < 30) digitalWrite(yellow1, HIGH);
  if (distance_cm < 40) digitalWrite(yellow2, HIGH);
  if (distance_cm < 50) digitalWrite(red1, HIGH);
  if (distance_cm < 60) digitalWrite(red2, HIGH);

  delay(300);
}
```

## Soldering Process
Here we use the Printed Circuit Board 
*Insert Picture of solder
*Insert Picture of Final project

## My notes
While doing this project, there were several findings or realizations I had during the process. The following are notes that I made.

### Wire placement on board matters
While first connecting everything to the breadboard before soldering, I realized that nothing would work. This made me soon realize that placement on the board matters. 
*Insert breadboard image

At first I wired everything to the original image that was given to us. This caused the wire current to not flow properly through the Ultrasonic board. After moving things around and further research on breadboard current, I was able to rewire my board and eventually got the sonic sensor to work.

### LED Long Pin Vs LED Short Pin
While connecting everything to the breadboard before soldering the final project, my LED lights would not turn on. After doing more research and asking for help. I realized that the LED Pins were backwards and I only had to flip them to get them to work. The short pin of the LED must recieve current from the wire and the long pin of the LED must recieve current from the resistor. This is because... 

### Discovering "Smooth" Jumpers
After soldering my final project, I noticed others had a much cleaner looking board compared to mine. Here I discovered that you can solder on wires to make them look nice and neat if still directed on the board. 
*Before image
*After Image

