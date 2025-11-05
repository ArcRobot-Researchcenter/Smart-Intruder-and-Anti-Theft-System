# Smart-Intruder-and-Anti-Theft-System
The Smart Intruder and Anti-Theft System is an IoT-based home and office security solution designed to detect intrusions, trigger alarms, and send instant SMS alerts to the owner even without internet connectivity.

Built on the ESP32 microcontroller, the system integrates:

* PIR motion detection for intrusion sensing

* Buzzer and LED indicators for alarm feedback

* EbulkSMS API for real-time SMS alerts

* SinricPro for remote arming/disarming via mobile app
* Google Voice Control
* Power Supply	5V USB or solar-compatible input

This solution provides affordable, subscription-free, and reliable smart security for homes, shops, hostels, and offices empowering individuals and SMEs to secure their spaces efficiently.

# Click to watch demo Testing 

[![Watch the video](https://img.youtube.com/vi/QvYmHDUJSlY/0.jpg)](https://youtu.be/QvYmHDUJSlY)


# ⚙️ Features

✅ Motion detection with PIR sensor
✅ Real-time SMS alert notification
✅ Alarm buzzer + LED indicators
✅ Remote arming/disarming through SinricPro
✅ Works without constant internet connection
✅ Compact and solar-compatible design

# 🧠 System Workflow

User arms the system via the SinricPro mobile app.

The PIR sensor continuously monitors for motion.

When motion is detected:

Alarm (buzzer + red LED) is triggered.

SMS alert is sent instantly via EbulkSMS API.

The system can be remotely disarmed or reset.

# 💻 Software & Technology Stack

Language: C++ (Arduino IDE)

Microcontroller: ESP32

APIs: EbulkSMS API

# 📂 Project Structure
Smart-Intruder-System/
│
├── Smart_Intruder_System.ino       # Main Arduino code
├── /images                         # Product and circuit images
├── /docs                           # Presentation & report files
└── README.md                       # Project overview (this file)

# 🔔 Setup Instructions

1. Clone the repository

git clone https://github.com/yourusername/Smart-Intruder-System.git

2. Open the project in Arduino IDE.

3. Install required libraries (WiFi, HTTPClient, ArduinoJson, SinricPro).

4. Replace the following credentials in the code:

5. Wi-Fi SSID & Password

6. EbulkSMS Username & API Key

7. SinricPro App Key, Secret, and Device ID

8. Upload to your ESP32 and power on the system.


# 📸 Screenshoot of the function:

The system detects motion, activates alarm, and sends an SMS alert instantly to the user’s phone.

<p align="center">
  <img src="https://github.com/ArcRobot-Researchcenter/Smart-Intruder-and-Anti-Theft-System/blob/main/image/Mobile%20app%20for%20theft%20system.jpg" width="30%" />
  <img src="https://github.com/ArcRobot-Researchcenter/Smart-Intruder-and-Anti-Theft-System/blob/main/image/Anti-theft-system.png" width="30%" />
  <img src="https://github.com/ArcRobot-Researchcenter/Smart-Intruder-and-Anti-Theft-System/blob/main/image/intruder-alert.jpg" width="30%" />
</p>


# Impact & Vision

This project was developed to address rising burglary incidents and limited access to affordable smart security in developing regions.
Our goal is to make low-cost, locally built IoT devices accessible to every Nigerian household and business.

# Solution Architecture / How It Works

The Smart Intruder and Anti-Theft System combines hardware sensors, IoT control, and cloud communication to provide real-time intrusion detection and instant alerts.
It follows a simple but powerful 3-layer architecture — Sensing Layer, Processing Layer, and Communication Layer.

# System Architecture Overview

1️⃣ Sensing Layer (Input Stage)

The PIR motion sensor continuously scans for movement within its detection range.

When motion is detected, it sends a HIGH signal to the ESP32 microcontroller.

2️⃣ Processing Layer (Decision Stage)

The ESP32 processes the sensor input.

If the system is armed, the microcontroller:

Activates the alarm outputs (buzzer + red LED).

Triggers the SMS notification function.

Sends a status update to the SinricPro cloud (for app control).

3️⃣ Communication Layer (Notification Stage)

The ESP32 uses Wi-Fi connectivity to reach:

EbulkSMS API, which sends an SMS alert to the user’s phone number.

SinricPro platform, enabling remote arming/disarming through a mobile app or voice assistant.

4️⃣ Output Layer (Response Stage)

The system gives an immediate audible and visual alert (buzzer + LED).

The owner receives an SMS alert like:

“⚠️ ALERT: Motion detected at your home! Take action immediately.”

The system resets automatically after a short interval (e.g., 30 seconds).

# 👨‍💻 Developer

Name: Abudlrahaman Raji
Organization: ARC ROBOT
Location: Ilorin, Kwara State, Nigeria
Contact: +23460031382

# 🏆 Acknowledgement

This project was showcased at Ilorin Innovation Hub – 2025 Innovation Challenge & Hackathon, focusing on IoT-driven security innovation.

# 📜 License

This project is released under the MIT License — open for learning, research, and non-commercial development.

# 💬 Contribute

Pull requests are welcome!
If you’d like to collaborate, improve the firmware, or extend new features (like mobile app integration or solar module), feel free to fork and contribute.
