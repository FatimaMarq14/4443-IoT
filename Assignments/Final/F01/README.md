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
- 🔌 Cleaner wiring and better power management

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

### 📟 Playing with the LCD

*Insert LCD image here*

- **What is it?** A screen that can display text or symbols.
- **What I wanted:** Show basic info like connection status, "Hello World", or control feedback.
- **What happened:** It worked alone, but not with the Bluetooth module connected.

---

### 🧩 Discovering I2C

*Insert I2C image here*

I learned about the **I2C protocol**, which allows multiple devices to communicate using just two wires (SDA and SCL). I switched to an **I2C backpack** for the LCD to save wiring space and reduce pin usage on the Arduino.

---

### 📦 HC-05 Bluetooth Module Arrives

*Insert HC-05 image here*

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
*Add image of voltage*

When I ran the code I did notice power going through both the bluetooth module and LCD screen which was a great relief for me! I was very excited and happy. However, when testing to get text on the LCD I saw nothing. This is where the next roadblobk came and had to find the problem. 

At this point I was stressed, wires were flying everywhere, and I honestly thought I might not finish on time.

---

### 🧠 Switching to ESP32
Thankfully, my professor introduced me to the ESP32, a more powerful board with built-in Bluetooth and Wi-Fi. This solved everything:
*Add image of ESP32 setup here*

- **What is it?** A more powerful microcontroller with **built-in** Bluetooth and Wi-Fi.
- **Why it saved me:** It supports multiple serial communications and it has built in bluetooth which means I no longer needed the bluetooth module or the voltage divider.

  After switching to the ESP32, everything was much smoother and cleaner. My LCD worked perfectly and now I just needed to look into the bluetooth part. 
---

### 📱 Remote XY App
Here, I designed a simple control panel with arrows for direction and a connect button.
*Add screenshot of Remote XY app layout*

The app helped me connect my Iphone to the ESP32. I followed a youtube tutorial online https://remotexy.com/ and i was able to easily controll my phone to the bluetooth. Now it was finally time to test my final code.

---

### 📱 Conclusion
This project taught me a lot about:
- How microcontrollers handle communication
- How to manage power and wiring in real projects
- Why choosing the right board matters

It wasn’t easy, but seeing the robot move via Bluetooth from my phone and display text on the LCD was worth it.

---
