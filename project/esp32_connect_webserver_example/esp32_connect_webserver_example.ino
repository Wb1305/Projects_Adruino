#include <WiFi.h>
#include <HTTPClient.h>

// Thay đổi các thông tin này theo cấu hình của bạn
const char* ssid = "n/w-b";
const char* password = "244466666";
const char* serverName = "https://example.com/";

void setup() {
  // Khởi động Serial
  Serial.begin(115200);

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Tạo đối tượng HTTPClient
  HTTPClient http;

  // Cấu hình URL và thực hiện yêu cầu GET
  http.begin(serverName);
  int httpResponseCode = http.GET();

  // Kiểm tra mã phản hồi
  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println("Response code: " + String(httpResponseCode));
    
    // Phân tích payload để lấy nội dung trong thẻ <p>
    extractParagraphs(payload);
  } else {
    Serial.println("Error code: " + String(httpResponseCode));
  }

  // Kết thúc kết nối
  http.end();
}

void loop() {
  // Không cần lặp lại trong ví dụ này
}

void extractParagraphs(const String& html) {
  int startIndex = 0;
  while (true) {
    startIndex = html.indexOf("<p>", startIndex);
    if (startIndex == -1) break;

    int endIndex = html.indexOf("</p>", startIndex);
    if (endIndex == -1) break;

    // Lấy nội dung giữa các thẻ <p>
    startIndex += 3; // Bỏ qua <p>
    String paragraph = html.substring(startIndex, endIndex);
    
    // In nội dung ra Serial Monitor
    Serial.println("Paragraph content: " + paragraph);

    // Cập nhật chỉ số để tiếp tục tìm kiếm
    startIndex = endIndex + 4; 
  }
}
