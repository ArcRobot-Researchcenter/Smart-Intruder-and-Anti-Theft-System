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

# Wireframe Design , Figma prototyping uisng wokwi ,  Hardware Sketch

<p align="center">
  <img src="https://github.com/ArcRobot-Researchcenter/Smart-Intruder-and-Anti-Theft-System/blob/main/image/Anti-theft-system2.png" width="30%" />
  <img src="https://github.com/ArcRobot-Researchcenter/Smart-Intruder-and-Anti-Theft-System/blob/main/image/Anti-theft-system.png%20simulator.png" width="30%" />
  <img src="https://github.com/ArcRobot-Researchcenter/Smart-Intruder-and-Anti-Theft-System/blob/main/image/circtut.jpg" width="30%" />
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

# view Source Code 
<details>
  <summary>📜 View Source Code (Click to Expand)</summary>

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <ArduinoJson.h>

// =============================
// USER SETTINGS
// =============================
const char* WIFI_SSID = "ARCRobot";
const char* WIFI_PASS = "@iceman247";

#define PIR_PIN      13
#define BUZZER_PIN   14
#define LED_ALARM    2
#define LED_STATUS   15  // shows armed/disarmed

// =============================
// INFOBIP API SETTINGS
// =============================
String apiKey     = "e79a4cd08058c273344f0859d52f061e-00571d77-9e89-4f2f-803b-01bae6eee39d";
String baseURL    = "https://rpd231.api.infobip.com/sms/2/text/advanced";
String sender     = "447491163443";
String recipient  = "2348060031382";

// =============================
// SINRICPRO CREDENTIALS
// =============================
#define APP_KEY    "fa5a5a72-6555-4771-a56c-b382f84cf885"
#define APP_SECRET "f1e2e0d6-7b33-46ed-82c7-34a4857c3db4-3691ba47-b891-40d9-9177-67e2194520c0"
#define DEVICE_ID  "68e844f3ba649e246c0a400d"

// =============================
// VARIABLES
// =============================
bool systemArmed = false;
bool alarmActive = false;
unsigned long lastSmsTime = 0;
const unsigned long SMS_COOLDOWN = 60000; // 1 min cooldown

// =============================
// FUNCTION TO SEND SMS VIA INFOBIP
// =============================
void sendSMS(String textMessage) {
  if (millis() - lastSmsTime < SMS_COOLDOWN) {
    Serial.println("[SMS] Cooldown active. Skipping message.");
    return;
  }

  Serial.println("[SMS] Sending via Infobip...");

  HTTPClient http;
  http.begin(baseURL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Accept", "application/json");
  http.addHeader("Authorization", "App " + apiKey);

  StaticJsonDocument<512> doc;
  JsonArray messages = doc.createNestedArray("messages");
  JsonObject msg = messages.createNestedObject();
  JsonArray destinations = msg.createNestedArray("destinations");
  JsonObject dest = destinations.createNestedObject();
  dest["to"] = recipient;
  msg["from"] = sender;
  msg["text"] = textMessage;

  String jsonPayload;
  serializeJson(doc, jsonPayload);

  int httpCode = http.POST(jsonPayload);

  if (httpCode > 0) {
    Serial.printf("[SMS] HTTP Response code: %d\n", httpCode);
    Serial.println(http.getString());
  } else {
    Serial.printf("[SMS] Error code: %d\n", httpCode);
  }

  http.end();
  lastSmsTime = millis();
}

// =============================
// PIR HANDLER
// =============================
void checkMotion() {
  if (digitalRead(PIR_PIN) == HIGH) {
    Serial.println("[PIR] Motion detected");

    if (systemArmed && !alarmActive) {
      Serial.println("[ALARM] Triggered!");
      alarmActive = true;

      digitalWrite(LED_ALARM, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);

      sendSMS("⚠️ ALERT: Motion detected at your home! Take action immediately.");
    }
  }
}

// =============================
// SINRIC HANDLERS
// =============================
bool onPowerState(const String &deviceId, bool &state) {
  systemArmed = state;
  digitalWrite(LED_STATUS, systemArmed ? HIGH : LOW);

  if (!systemArmed && alarmActive) {
    alarmActive = false;
    digitalWrite(LED_ALARM, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  Serial.printf("[SinricPro] System %s\n", systemArmed ? "ARMED" : "DISARMED");
  return true;
}

// =============================
// SETUP
// =============================
void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_ALARM, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);

  digitalWrite(LED_ALARM, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_STATUS, LOW);

  Serial.println("[WiFi] Connecting...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[WiFi] Connected!");

  SinricProSwitch &mySwitch = SinricPro[DEVICE_ID];
  mySwitch.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

// =============================
// LOOP
// =============================
void loop() {
  SinricPro.handle();
  checkMotion();

  if (alarmActive && millis() - lastSmsTime > 30000) {
    alarmActive = false;
    digitalWrite(LED_ALARM, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("[ALARM] Reset after 30s.");
  }
}
