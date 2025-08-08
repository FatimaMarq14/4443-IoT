# 🤖 Bluetooth Controlled Robot Code

**Student Name:** Fatima Marquez

## 🧠 Project Description
This final project is a custom-built robot powered by an ESP32. It is capable of movement, displaying status on an LCD, and being controlled via Bluetooth. The project demonstrates skills in embedded systems, hardware integration, and Arduino programming.

## 📂 Code

| File Name            | Description                                         |
|----------------------|-----------------------------------------------------|
| `main.ino`           | Main Arduino code for ESP32                         |

---

## 🛠️ Tools & Languages
| Component              | Notes                          |
|------------------------|--------------------------------|
| Language      | C++ (Arduino dialect)                   |
| Platform      | ESP32                                   |
| IDE           | Meant for the Arduino IDE or PlatformIO |
| RemoteXY      | Bluetooth App                           |

---

## 🔍 Type of Code:

| Libraries           | Notes                                    |
|---------------------|------------------------------------------|
| RemoteXY.h          | for Bluetooth GUI interface via RemoteXY |
| LiquidCrystal_I2C.h | for I2C LCD screen control               |
| Wire.h              |  I2C communication                       |
| BLEDevice.h         | for Bluetooth communication on the ESP32 |

---

## 📂 In Depth Code Explanation

This line of code is a preprocessor directive used in code that works with the RemoteXY platform, which allows you to create a mobile app interface to control the ESP32 over Bluetooth.
```cpp
#define REMOTEXY_MODE__ESP32CORE_BLE
```

These are the libraries used that are explained above.
```cpp
#include <BLEDevice.h>
#include <RemoteXY.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

When connecting to the app, other bluetooth modules also appear. Here we are giving the ESP32 to show up as **BEEP**, that way we are able to distinct it from the rest.
```cpp
// RemoteXY Bluetooth name
#define REMOTEXY_BLUETOOTH_NAME "BEEP"
```

Before setting up the code we first have to create the controller GUI from the RemoteXY website. Once we set up our controller GUI, the website will generate
```cpp
// RemoteXY GUI config
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = {
  255,4,0,0,0,64,0,19,0,0,
  0,0,31,1,106,200,1,1,4,0,
  1,35,58,32,32,0,2,31,85,112,
  0,1,35,119,32,32,0,2,31,68,
  111,119,110,0,1,4,87,32,32,0,
  2,31,76,101,102,116,0,1,66,86,
  32,32,0,2,31,82,105,103,104,116,0
};
```

```cpp
struct {
  uint8_t btn_up;
  uint8_t btn_down;
  uint8_t btn_left;
  uint8_t btn_Right;
  uint8_t connect_flag;
} RemoteXY;
#pragma pack(pop)
```

```cpp
// LCD on I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

```cpp
// Motor pins
const int IN1 = 13;
const int IN2 = 12;
const int IN3 = 14;
const int IN4 = 27;
```

```cpp
// Message to scroll
String message = "    4443 - Internet of Things    ";
unsigned long lastScroll = 0;
int scrollDelay = 300;
```

```cpp
void setup() {
  RemoteXY_Init();

  // LCD Setup
  Wire.begin(21, 22);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting MangoBot");

  // Motor setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors(); // Ensure stopped on boot
}
```

```cpp
void loop() {
  RemoteXY_Handler();

  // Scroll message
  scrollLCDMessage();

  // Handle motor control
  if (RemoteXY.btn_up) {
    moveForward();
    showDirection("FORWARD");
  }
  else if (RemoteXY.btn_down) {
    moveBackward();
    showDirection("BACKWARD");
  }
  else if (RemoteXY.btn_left) {
    turnLeft();
    showDirection("LEFT");
  }
  else if (RemoteXY.btn_Right) {
    turnRight();
    showDirection("RIGHT");
  }
  else {
    stopMotors();
    showDirection("STOPPED");
  }

  delay(50); // Keep things smooth
}

// Scroll text on LCD line 0
void scrollLCDMessage() {
  static int scrollIndex = 0;
  if (millis() - lastScroll >= scrollDelay) {
    lastScroll = millis();

    String toDisplay = message.substring(scrollIndex, scrollIndex + 16);
    lcd.setCursor(0, 0);
    lcd.print(toDisplay);

    scrollIndex++;
    if (scrollIndex > message.length() - 16) {
      scrollIndex = 0;
    }
  }
}

// LCD status on line 1
void showDirection(String msg) {
  lcd.setCursor(0, 1);
  lcd.print("Moving: " + msg + "   ");
}

// Motor functions
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

```

---
