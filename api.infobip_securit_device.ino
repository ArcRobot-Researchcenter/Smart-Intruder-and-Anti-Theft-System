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
String sender     = "447491163443";     // can be alphanumeric or a valid number
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

  // Construct JSON payload
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

  // Reset alarm automatically after 30 seconds
  if (alarmActive && millis() - lastSmsTime > 30000) {
    alarmActive = false;
    digitalWrite(LED_ALARM, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("[ALARM] Reset after 30s.");
  }
}
