#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

// المكونات
const int buttonPin = 2;
const int ledPin = 3;
const int pirPin = 4;
const int ldrPin = A0;

// المتغيرات
bool lastButtonState = HIGH;
bool manualMode = false;
bool userTurnedOffLight = false;

unsigned long lastMotionTime = 0;
const unsigned long motionTimeout = 20000;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  Serial.begin(9600);

  // تهيئة الشاشة
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // قراءة الزر للتبديل بين الوضع اليدوي والتلقائي
  bool currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    manualMode = !manualMode;
    lastMotionTime = millis(); // إعادة ضبط التوقيت عند التبديل

    if (!manualMode) {
      userTurnedOffLight = true;
      analogWrite(ledPin, 0);
    }
    delay(200);
  }
  lastButtonState = currentButtonState;

  // قراءة الحساسات
  int lightValue = analogRead(ldrPin);
  bool motionDetected = digitalRead(pirPin);

  // عرض في Serial Monitor
  Serial.print("LDR: ");
  Serial.print(lightValue);
  Serial.print(" | Motion: ");
  Serial.print(motionDetected);
  Serial.print(" | Mode: ");
  Serial.println(manualMode ? "Manual" : "Auto");

  // عرض على شاشة LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode: ");
  lcd.print(manualMode ? "Manual" : "Auto");

  lcd.setCursor(0, 1);
  lcd.print("L:");
  lcd.print(lightValue);
  lcd.print(" M:");
  lcd.print(motionDetected);

  // تحديث وقت الحركة
  if (motionDetected) {
    lastMotionTime = millis();
  }

  // -------- الوضع اليدوي --------
  if (manualMode) {
    userTurnedOffLight = false;

    if (lightValue > 500) {
      analogWrite(ledPin, 0);
    } else {
      if (motionDetected) {
        analogWrite(ledPin, 255);
      } else {
        analogWrite(ledPin, 80);
      }
    }

  // -------- الوضع التلقائي --------
  } else {
    if (lightValue > 500) {
      analogWrite(ledPin, 0);
    } else {
      if (motionDetected) {
        if (userTurnedOffLight) {
          analogWrite(ledPin, 80);
        } else {
          analogWrite(ledPin, 255);
        }
      } else {
        if (millis() - lastMotionTime > motionTimeout) {
          analogWrite(ledPin, 80);
          userTurnedOffLight = false;
        } else {
          analogWrite(ledPin, 0);
        }
      }
    }
  }

  delay(200);
}
