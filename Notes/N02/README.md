## Multiplexing / LED Matrix

### Given: "Here's something to think about: Given an NxN matrix of LED's, how would you wire it so that it wasn't ridiculous? Remember on our bread boards its one resister per LED!!"

3 LED Matrix Modules <br/>
MAX7219 <br/>
Pins (headers)

### Example:
To turn on **1 lightbulb** you need: 
- One wire to send power
- One wire to connect it to ground
- One resistor to protect it from too much power <br/>

To turn on **64 lightbulbs** you need: 
- 64 resistors
- 64 wires
- 64 pins — which is impossible on most beginner boards like Arduino Uno (it only has ~14 usable pins)

Instead, the MAX7219 is able to make this less ridiculous.

## Max7219
- Each module includes a grid of LED's arranged in 8 rows and 8 columns called an 8x8 LED Matrix
- Controls 64 LEDs (8x8) using only 3 microcontroller pins via SPI.
- The **MAX7219** has built-in current limiting, so you dont need a resistor per LED
- Can **diasy chain** to make larger displays

So one module controls **64** lights. 3 connected together control **192** lights with minimum wires or pins.

## Without MAX7219
If the **MAX7219** was not available then you would have to use multiplexing _manually_. 

1. Rows and Columns
   - Wire all the LED cathodes to rows and anodes to columns (or vice versa).
   - To turn on a specific LED, you power the right column and ground the corresponding row.
   - For N×N LEDs, you only need 2N GPIO pins instead of N².
##### Drawbacks:
- Still need resistors for each row/column to prevent overcurrent.
- Requires timing logic to cycle through rows/columns quickly (PWM + multiplexing).
- Lots of code and tight timing loops — can be done, but gets messy.

