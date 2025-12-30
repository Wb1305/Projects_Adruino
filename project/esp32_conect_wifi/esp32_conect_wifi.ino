#include <WiFi.h>

const char* ssid = "n/w-b";
const char* password = "244466666";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("ESP32 localIP:");
  Serial.print(WiFi.localIP());
  Serial.println("ESP32 MAC address:");
  Serial.print(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:

}