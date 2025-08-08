/****** MangoBot: ESP32 + LCD + RemoteXY + L298N Motor Control ******/

#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>
#include <RemoteXY.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RemoteXY Bluetooth name
#define REMOTEXY_BLUETOOTH_NAME "MANGOBOT"

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

struct {
  uint8_t btn_up;
  uint8_t btn_down;
  uint8_t btn_left;
  uint8_t btn_Right;
  uint8_t connect_flag;
} RemoteXY;
#pragma pack(pop)

// LCD on I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Motor pins
const int IN1 = 13;
const int IN2 = 12;
const int IN3 = 14;
const int IN4 = 27;

// Message to scroll
String message = "    4443 - Internet of Things    ";
unsigned long lastScroll = 0;
int scrollDelay = 300;

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
