🔧 Bluetooth-Controlled Robot Car (Arduino + HC-05 + L293D IC)

This project is a simple Bluetooth-controlled robot car built with components I had lying around.
The goal was to control a basic 4-motor robot using my phone’s Bluetooth, and later, extend it with an ESP32-based joystick controller (so my phone can rest 😅).

 Overview

The car is driven by 4 L293D motor driver ICs, controlled directly by the Arduino Uno.
Communication happens over Bluetooth using an HC-05 module paired with a mobile app interface that sends directional commands.

Each command (located under the switch statement located in the code) maps to forward, backward, left, and right motion, while another button controls a passive buzzer for horn sound.

 Hardware Used

Arduino Uno (Main controller)

2 × L293D ICs (Dual H-bridge motor drivers)

HC-05 Bluetooth module (Serial communication)

2 DC Motors (Tank-style drive)

Passive buzzer

~8V Battery pack (Power supply through VIN)

Wires, breadboard, and chassis

🧩 Wiring Summary
Component	Arduino Pin	Notes
Motor 1 EN	10	PWM for speed control
Motor 1 IN1	9	Direction
Motor 1 IN2	8	Direction
Motor 2 EN	5	PWM
Motor 2 IN1	2	Direction
Motor 2 IN2	7	Direction
Motor 3 EN	6	PWM
Motor 3 IN1	A2	Direction
Motor 3 IN2	A3	Direction
Motor 4 EN	11	PWM
Motor 4 IN1	A0	Direction
Motor 4 IN2	A1	Direction
HC-05 TX	Arduino Pin 3	SoftwareSerial RX
HC-05 RX	Arduino Pin 2	SoftwareSerial TX
Buzzer	6	Passive buzzer output
💻 Code Summary

SoftwareSerial is used to communicate with the HC-05 on pins 2 and 3.

The app sends characters as 'F' for forward, 'B' for backward, etc. as stated in the program.

A switch statement handles direction and buzzer logic.

The buzzer is only active when pressed (passive tone controlled via tone() and noTone()).

 Next Steps

Replace phone control with ESP32 joystick control (Bluetooth master–slave setup).

Add simple IR sensors for autonomous line following

Develop a simple web dashboard to log and visualize control inputs.

🧾 License

Open for learning and tinkering purposes.
Feel free to use or modify, just mention me if you build upon it!
