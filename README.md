# Smart Latching Power System
 This project is a smart latching power switch It can turn lights ON and OFF automatically or manually. 
 Use and program both digital and analog sensors, We use a light sensor (LDR) and a motion sensor (PIR) to control the system.

---

## Goal 1

### Smart Latching Power Switch with Auto Mode

* The system has a **button** to switch between:

  * **Manual Mode**: The user controls the light.
  * **Auto Mode**: The system controls the light based on sensors.
* In **Auto Mode**:

  * If it’s **dark** and there is **motion** → the light turns **on**.
  * If there is **no motion for 20 seconds** → the light becomes **dim**.
  * If the **light level is high** (like sunlight) → the light stays **off**.
* If the user turns off the light in Manual Mode, then switches to Auto Mode → the system keeps the light dim to respect user choice.

---

## Goal 2

### Sensors and Components Used

| Component        | Type       | Function                              |
| ---------------- | ---------- | ------------------------------------- |
| **LDR**          | Analog     | Reads brightness (0 to 1023)          |
| **PIR Sensor**   | Digital    | Detects motion (HIGH / LOW)           |
| **Button**       | Digital    | Changes between Manual and Auto modes |
| **LED Light**    | PWM Output | Acts as the lamp (brightness control) |
| **LCD 16x2 I2C** | Digital    | Shows mode, light value, and motion   |

---

## LCD Display

Shows two lines:

* `Mode: Manual` or `Mode: Auto` (current mode)
* `L:<light>` and `M:<motion>` (sensor values)

---

## System Behavior

### Manual Mode:

* Bright room → light stays OFF (even if motion)
* Dark + motion → light turns ON (full brightness)
* Dark + no motion → light is DIM

### Auto Mode:

* Bright room → light stays OFF
* Dark + motion → light turns ON (unless user turned it off before)
* Dark + no motion for 20 sec → light becomes DIM

---

## Used Components

* Arduino UNO
* PIR motion sensor
* LDR light sensor
* Push button
* LED light + resistor
* LCD 16x2 (I2C, address 0x27)
* Breadboard + jumper wires

---

## 📷 Project Snapshot
<img width="1232" height="547" alt="Super Jarv" src="https://github.com/user-attachments/assets/6332c1f1-13c5-4764-b1cd-68e73882f069" />


---

## 🧠 Smart Notes

* Used `analogWrite()` for brightness control (PWM).
* Used `millis()` instead of `delay()` to track motion timeout.
* The light is automatically off if the room is already bright.
