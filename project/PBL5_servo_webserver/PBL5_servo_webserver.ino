#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

// Thay đổi các thông tin này theo cấu hình của bạn
const char* ssid = "Tro 123";
const char* password = "tudoanpasss*#";
const char* serverName = "https://40f4-34-170-93-130.ngrok-free.app/show-image";

Servo servo1;
Servo servo2;

const int ledPin=2;
const int sv1Pin=17;
const int sv2Pin=16;
const int cb1Pin = 34;        // Chân của cảm biến hồng ngoại 1 (cb1)
const int cb2Pin = 35;        // Chân của cảm biến hồng ngoại 2 (cb2)

void setup() {
  // Khởi động Serial
  Serial.begin(115200);
  // Initialize LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Ensure LED is off at startup
  // initialize servo pin
  servo1.attach(sv1Pin, 500, 2500);
  servo2.attach(sv2Pin, 500, 2500); // Gán chân cho servo2
  
  pinMode(cb1Pin, INPUT);  // Thiết lập cb1 là đầu vào
  pinMode(cb2Pin, INPUT);  // Thiết lập cb2 là đầu vào
  // Kết nối WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Không cần lặp lại trong ví dụ này
  // getDataFromServer(serverName);
  controlServo(serverName);
  delay(5000);
}

String getDetailFromJson(const String& jsonString) {
  // Create a JSON document
  StaticJsonDocument<200> doc; // Adjust size as needed

  // Deserialize the JSON string
  DeserializationError error = deserializeJson(doc, jsonString);

  // Check for errors
  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.f_str());
    return "";
  }

  // Get the value of "detail"
  String detail = doc["detail"].as<String>();
  return detail;
}

// void controlLed(const String& detailValue) {
//   // Check if detail is "ok" and turn on/off the LED
//   if (detailValue == "No image found") {
//     // digitalWrite(ledPin, HIGH); // Turn on LED
//     // delay(5000);
//     // digitalWrite(ledPin, LOW); // Turn off LED
//     Serial.println("LED ON");
//   } else {
//     // digitalWrite(ledPin, LOW); // Turn off LED
//     Serial.println("LED OFF");

//   }
// }

String getDataFromServer(const char* serverName){
  // Tạo đối tượng HTTPClient
  HTTPClient http;

  // Cấu hình URL và thực hiện yêu cầu GET
  http.begin(serverName);
  int httpResponseCode = http.GET();
  String data="";
  // Kiểm tra mã phản hồi
  if (httpResponseCode > 0) {
    String payload = http.getString();
    // Serial.println("Response code: " + String(httpResponseCode));
    
    // Phân tích payload để lấy nội dung trong thẻ <p>
    data = getDetailFromJson(payload);
    Serial.println("payload:" + data);
  } else {
    Serial.println("Error code: " + String(httpResponseCode));
  }

  // Kết thúc kết nối
  http.end();
  return data;
}

void controlServo(const char* serverName){
  String data = getDataFromServer(serverName);
  int sensorValue1, sensorValue2 = readValueFromSensor();
  controlServo1(data, sensorValue1);
  controlServo1(data, sensorValue2);
}

void controlServo1(const String& detailValue, int sensorValue){
  // Kiểm tra điều kiện để điều khiển servo1
  if (detailValue == "onservo1" && sensorValue == 0) {
    servo1.write(90);      // Quay servo1 đến góc 90 độ
    delay(2000);           // Giữ vị trí trong 1 giây
    servo1.write(0);       // Trả về góc 0 độ
  }
}

void controlServo2(const String& detailValue, int sensorValue){
  // Kiểm tra điều kiện để điều khiển servo2
  if (detailValue == "onservo2" && sensorValue == 0) {
    servo2.write(90);      // Quay servo2 đến góc 90 độ
    delay(2000);           // Giữ vị trí trong 1 giây
    servo2.write(0);       // Trả về góc 0 độ
  }
}

int readValueFromSensor(){
  int sensorValue1 = digitalRead(cb1Pin);
  int sensorValue2 = digitalRead(cb2Pin);
  if (sensorValue1 == 1) {
      Serial.println("Cảm biến hồng ngoại 1 không phát hiện vật cản.");

  } else {
      Serial.println("Cảm biến hồng ngoại phát hiện vật cản.");
  }
  if (sensorValue2 == 1) {
      Serial.println("Cảm biến hồng ngoại 2 không phát hiện vật cản.");

  } else {
      Serial.println("Cảm biến hồng ngoại phát hiện vật cản.");
  }
  return sensorValue1, sensorValue2;
}

