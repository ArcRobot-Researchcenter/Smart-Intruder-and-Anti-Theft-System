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
