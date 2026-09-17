# 🚗 Automotive Event Data Recorder — Black Box (PIC18F4580)
 
A single-node automotive "black box" built on a PIC18F4580, logging gear changes and crash/impact events with an RTC-stamped timestamp into external EEPROM — modeled after a real vehicle Event Data Recorder (EDR). **Built 2 core embedded protocols : I2C (RTC + EEPROM communication) and UART (serial log download)**.
 
## 📋 Overview
 
This project simulates a simplified in-vehicle black box: live gear + speed telemetry is shown on a character LCD dashboard, key driving events (gear shifts, simulated crash/impact) are timestamped using a DS1307 RTC and written to non-volatile external EEPROM, and the full log can be reviewed on-device or downloaded over UART — the same core idea used in real automotive EDR / crash-data-recorder systems.
 

<img width="3089" height="8603" alt="diagram" src="https://github.com/user-attachments/assets/c07d7c6b-46af-4caf-ac5d-20d00219bc11" />

 
## 🧩 Core Modules
 
| Module | Role | Notes |
|---|---|---|
| Matrix Keypad 🔢 | Gear up/down, crash-simulate button, menu access | 3x2 scanned matrix — SW1 (gear up), SW2 (gear down), SW3 (simulate crash), SW10/SW11/SW12 (menu nav/select/back) |
| ADC 🎚️ | Speed input | Potentiometer on analog channel, 10-bit right-justified, converted and displayed as 0–100 |
| DS1307 RTC 🕒 | Real-time clock | I2C-based, drives every log entry's timestamp; time/date settable from the on-device menu |
| External EEPROM 💾 | Non-volatile event log | I2C EEPROM (device address 0xA0/0xA1), stores up to 15 timestamped log strings, circular write-count tracking |
| CLCD 🖥️ | Live dashboard | 16x2 character LCD — shows RTC time, current gear, and speed; switches to a "CRASH" banner on impact |
| UART 📶 | Log export | Dumps the full black-box log as formatted text to a serial terminal |
| Menu 📋 | On-device log browser | Keypad-driven menu: View Log, Download Log, Set RTC, Clear Log |
 
## ✨ Features
 
- 🕒 **DS1307 RTC-stamped event logging** — every gear change and every simulated crash writes a `"<event> - <timestamp>"` entry to EEPROM
- 💥 **Simulated crash/impact button** — triggers a latched "CRASH" screen on the LCD and logs the event with timestamp
- ⚙️ **Gear tracking** (N, 1–5) via keypad, shown live on the dashboard alongside speed
- 🎚️ **ADC-based analog speed simulation** (10-bit, right-justified), scaled to a 0–100 display value
- 💾 **Circular external I2C EEPROM log store** (up to 15 entries), with view, download, and clear operations
- 🖥️ **On-device menu system** (View Log / Download Log / Set Log (RTC) / Clear Log) navigated entirely from the matrix keypad
- 📶 **UART log download** — dumps the complete black-box log as readable text over serial
- ⏱️ **Timer1-interrupt-driven timeouts** for scroll/hold/menu, decoupled from the main polling loop

-------

## Working Demonstration 📽️


- 📃 View Option Demo


https://github.com/user-attachments/assets/caf3b312-3005-44ce-ac6c-3261c11519d6

---
- Download Log Demo : UART Tx 📡


https://github.com/user-attachments/assets/2779c6b8-0796-4383-a94b-9c4167a63a70

---
- Set Log Demo : I2c - DS1307 ⏱️ Update

  
https://github.com/user-attachments/assets/8e40a761-471c-4b43-84b7-579e912abc9f

---
- Clear Log Demo : I2c - 24C04 (Ext EEPROM) Clear 🔧


https://github.com/user-attachments/assets/a1f7509b-d33b-42d7-914d-e6f6878117e8


-------
## 🔧 Hardware
 
- 🧠 PIC18F4580 microcontroller
- 🕒 DS1307 RTC module (I2C)
- 💾 External I2C EEPROM (e.g. 24LC-series, address 0xA0/0xA1)
- 🖥️ 16x2 character LCD
- 🔢 3x2 matrix keypad (gear up/down, crash simulate, menu nav/select/back)
- 🎚️ Potentiometer on ADC channel for speed simulation
- 🔌 UART-to-USB adapter for log download to a PC terminal
## 📁 Repository Structure
 
```
main.c                    # Init + main polling loop
Clock.c / Clock.h         # Timer1 tick source (scroll/hold/menu timers)
adc.c / adc.h             # Speed ADC channel config + read
Matrix_Keypad.c / .h      # Keypad scan, gear control, crash trigger
clcd.c / clcd.h           # LCD driver + live dashboard line formatting
ds1307.c / ds1307.h       # RTC driver, time get/set, RTC-set menu UI
I2c.c / I2c.h             # I2C bus driver (RTC + EEPROM)
Ext_EEPROM.c / .h         # Event log write/read/clear on external EEPROM
Menu.c / Menu.h           # Keypad-driven on-device menu system
UART.c / UART.h           # Serial log download
Enable.h / interrrupt.c   # Global interrupt enable + ISR (ADC, Timer1)
```
 
This is a single MPLAB X IDE project (XC8 toolchain).
 
## 🛠️ Building & Flashing
 
1. 📂 Open the project folder in **MPLAB X IDE**.
2. ⚙️ Ensure the **XC8 compiler** is installed and selected as the toolchain.
3. 🎯 Set the target device to **PIC18F4580**.
4. 🔨 Build (production configuration) and flash via **PICkit/ICD**.
5. 🔗 Wire up the CLCD, matrix keypad, DS1307 RTC, and external EEPROM as per the pin macros in each module's header, then power on — the dashboard starts showing live RTC time / gear / speed immediately.
## 🎮 Controls
 
| Key | Function |
|---|---|
| SW1 | Gear up (on dashboard) / Scroll down (in menu) |
| SW2 | Gear down (on dashboard) / Scroll up (in menu) |
| SW3 | Simulate crash/impact event |
| SW10 / SW11 | Open menu / Select menu item |
| SW12 | Back / Exit menu |
 
## 🐛 Debugging Notes
 
- 🔁 The I2C driver originally never cleared `PIR1bits.SSPIF` after Start/Stop/ACK/NACK sequences, so `I2c_Write`/`I2c_Read` returned before the real byte transfer finished — this was the root cause of garbage values being read back from the external EEPROM. Fixed by clearing the flag at the end of `I2c_Start`, `I2c_Stop`, `I2c_ACK`, and `I2c_NACK`, and adding a proper `I2c_ReStart()` (using RSEN) instead of calling `I2c_Start()` twice for a repeated start.
- 🕒 DS1307 RTC driver with a keypad-based set-time UI was added after the base dashboard + logging was working.
## 🚀 Possible Extensions
 
- 🔄 Move keypad/menu polling to an interrupt- or event-driven model
- 🛑 Add EEPROM write-protect / wear-leveling for long-term logging
- 📈 Log actual accelerometer/impact-sensor data instead of a simulated crash button
- 🖼️ Replace the character LCD with a graphical display for richer event detail
- 🌐 Stream live log entries out over UART instead of only on-demand download
## 👤 About Me
 
**JITHIN P**
🎓 Electronics and Communication Engineering graduate
📍 Bengaluru, India
 
**Skilled in:**
- 🔩 Embedded Systems & Bare-Metal Coding
- 💻 Firmware Development
- 🧮 Data Structures & Algorithms (DSA)
- ⚡ C++
- 🔧 C Programming
- 🐧 Linux Internals
- 📡 Protocols: CAN, SPI, I2C, UART
## 🔗 Connect with me
[GitHub](#) · [LinkedIn](#)
 
