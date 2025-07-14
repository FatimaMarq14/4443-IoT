# Servo Intro

The following is where I am getting comfortable with the arduino. Here I will go over different mini projects that I tested to get introduced to the basics.

## Servo
##### Here I will make 
*insert image




### Connection Schematic
*insert image

A connection schematic, also known as a wiring diagram, is a visual representation of how electrical components are physically connected in a circuit. Here I used:
- (1) x Elegoo Uno R3
- (1) x servo (SG90)
- (4) x M-M wires (Male to Male jumper wires)

A servo can only rotate 180 degrees. Its conrolled by sending electrical pulses that then tell the servo which positions to move. 

### How It Works:
- The servo has 3 wires
  - brown
  - red
  - 

### Arduino Code:
```cpp
#include <Servo.h>
/* After including the corresponding libraries,
   we can use the "class" like "Servo" created by the developer for us.
   We can use the functions and variables created in the libraries by creating 
   objects like the following "myservo" to refer to the members in ".".*/

Servo myservo;
//it created an object called myservo.
/*  you can see Servo as a complex date type(Including functions and various data types)
    and see myservo as variables.               */

void setup(){
  /*"attach" and "write" are both functions,
     and they are members contained in the complex structure of "Servo". 
     We can only use them if we create the object "myservo" for the complex structure of "Servo".
  */
  myservo.attach(9);//connect pin 9 with the control line(the middle line of Servo) 
  myservo.write(90);// move servos to center position -> 90°
} 
void loop(){
  myservo.write(90);// move servos to center position -> 90°
  delay(1000);
  myservo.write(60);// move servos to center position -> 60°
  delay(1000);
  myservo.write(90);// move servos to center position -> 90°
  delay(1000);
  myservo.write(150);// move servos to center position -> 120°
  delay(1000);
}

```
