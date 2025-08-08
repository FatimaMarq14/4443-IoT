# 🤖 Bluetooth-Controlled Robot Car

## 📌 Overview

For this class, we were tasked with designing a final project using microcontrollers. I started with a basic robotic car kit that could be controlled with a remote. But after learning more about components and how they work, I decided to level up my project and create a **Bluetooth-controlled robot** with an **LCD feedback display**.

At first, I thought it would be simple—connect the components, power them up, and everything would work together. That was *not* the case. I ran into wiring problems, serial communication conflicts, and power limitations. What began as a fun idea became a full hands-on learning experience in debugging, circuit design, and upgrading microcontrollers.

---

## 📸 Demo

*(Insert GIF or image here)*  
![Demo](demo.gif)

---

## ⚙️ Features

- 📱 Bluetooth control using the RemoteXY app
- 🖥️ LCD display to show live feedback and status
- 🔄 Upgraded to ESP32 for built-in Bluetooth and more serial support

---

## 🌱 Future Ideas

- 🧊 3D-printed case for better protection and style
- 🧠 Object avoidance using ultrasonic sensors
- 🎙️ Voice-controlled commands via mobile assistant

---

## 🧰 Components Used

| Component              | Used? | Notes                                           |
|------------------------|-------|-------------------------------------------------|
| ESP32 Microcontroller  | ✅    | Final board used – built-in Bluetooth!         |
| Arduino Uno (Elegoo)   | ❌    | Used for testing but replaced with ESP32       |
| HC-05 Bluetooth Module | ❌    | Originally planned, not needed after ESP32     |
| L298N Motor Driver     | ✅    | Controls the two DC motors                     |
| I2C LCD Display        | ✅    | Shows messages/status updates                  |
| Power Bank / Batteries    | ✅    | External power for motors and ESP32            |

---

## 🛠️ Tools & Languages

- Arduino IDE
- C++ (Arduino)
- RemoteXY App
- Multimeter (for testing voltage + continuity)

---

## 🧪 Build Journal

### 🧱 Starting Out

I began with the Arduino Uno and a 2WD robotic car kit. I wanted to control the car using Bluetooth while showing text on an LCD. However, the Uno didn’t have enough serial ports or power to handle both the HC-05 and the LCD at the same time.

---

## 🔩 Car Assembly

The car frame was assembled by attaching:

- **DC motors** to each side of the chassis using screws and brackets.
- **L298N motor driver** placed centrally to balance weight.
- **Battery holder** secured in the front.
- **Caster wheel** on the back for mobility.
- Components mounted with screws.

This created a stable, mobile base for the bot.

---

## 🌀 Motors
<img width="400" height="400" alt="image" src="https://github.com/FatimaMarq14/4443-IoT/blob/main/Assignments/Final/F01/Motor%20Driver.jpeg" />


Two **DC motors** were used for movement, each connected to the **L298N motor driver** via its OUT1/OUT2 and OUT3/OUT4 terminals.

The **IN1–IN4** pins of the L298N were connected to the ESP32 GPIO pins for directional control:
- IN1 → GPIO 13
- IN2 → GPIO 12
- IN3 → GPIO 14
- IN4 → GPIO 27

The **EN-A** and **EN-B** pins were bridged or connected to 5V to keep the motors always enabled.

Power was supplied to the motor driver via the battery pack, using 7.4V total from two 18650 batteries.

---

### 📟 Playing with the LCD

<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/774ecc44-b279-4502-a18c-fc0475b2412f" />


- **What is it?** A screen that can display text or symbols.
- **What I wanted:** Show basic info like connection status, "Hello World", or control feedback.
- **What happened:** It worked alone, but not with the Bluetooth module connected.

---

### 🧩 Discovering I2C

<img width="400" height="400" alt="image" src="https://github.com/FatimaMarq14/4443-IoT/blob/main/Assignments/Final/F01/I2C.jpeg" />


I learned about the **I2C protocol**, which allows multiple devices to communicate using just two wires (SDA and SCL). I switched to an **I2C backpack** for the LCD to save wiring space and reduce pin usage on the Arduino.

---

### 📦 HC-05 Bluetooth Module Arrives

<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/a2da4ae3-a056-4ffa-81a0-67aa4a2686ce" />


I was super excited to test the Bluetooth, but quickly ran into problems. I didn’t have enough GND pins on the Arduino, and the HC-05 needed special voltage treatment to avoid burning out.

---

### ⚠️ The Arduino Roadblock

To get both the LCD and HC-05 working, I needed to make a **voltage divider** and add resistors so the 5V signals wouldn’t damage the 3.3V HC-05.

💡 **Voltage Divider Example:**

```plaintext
[Arduino TX] --- [1kΩ] ---+--- [Bluetooth RX]
                          |
                        [2kΩ]
                          |
                        [GND]

[Arduino RX] <--- [Bluetooth TX] (direct)

[Bluetooth VCC] ---> [L298N 5V]
[Bluetooth GND] ---> [L298N GND]

```

---

### 🔌 Discovering Voltage Dividers 
This is the final image of me attempting to make the voltage divider. 
<img width="400" height="400" alt="image" src= "https://github.com/FatimaMarq14/4443-IoT/blob/main/Assignments/Final/F01/Voltage%20Divider.jpeg" />

When I ran the code I did notice power going through both the bluetooth module and LCD screen which was a great relief for me! I was very excited and happy. However, when testing to get text on the LCD I saw nothing. This is where the next roadblobk came and had to find the problem. 

At this point I was stressed, wires were everywhere, and I honestly thought I might not finish on time.

---

### 🧠 Switching to ESP32
Thankfully, my professor introduced me to the ESP32, a board with built-in Bluetooth and Wi-Fi. This solved everything:
<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/8cffaff3-6418-421d-bfbb-27934942a8a2" />

- **Why it saved me:** It supports multiple serial communications and it has built in bluetooth which means I no longer needed the bluetooth module or the voltage divider.

  After switching to the ESP32, everything was much smoother and cleaner. My LCD worked perfectly and now I just needed to look into the bluetooth part. 
---

### 📱 Remote XY App
The app helped me connect my Iphone to the ESP32. Here, I designed a simple control panel with arrows for directions.
<img width="400" height="400" alt="image" src="https://github.com/FatimaMarq14/4443-IoT/blob/main/Assignments/Final/F01/Controller.PNG" />

I followed a youtube tutorial online https://remotexy.com/ and i was able to easily controll my phone to the bluetooth.

---

### 📱 Conclusion
This project taught me a lot about:
- How microcontrollers handle communication
- How to manage power and wiring in real projects
- Why choosing the right board matters

It wasn’t easy, but seeing the robot move via Bluetooth from my phone and display text on the LCD was worth it.

---
