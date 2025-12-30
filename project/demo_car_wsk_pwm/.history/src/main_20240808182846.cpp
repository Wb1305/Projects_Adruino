#include <WiFi.h>
#include <WebServer.h>
#include <esp_camera.h>

// Thay đổi với SSID và Password của mạng WiFi của bạn
const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

WebServer server(80);

void setup()
{
  Serial.begin(115200);

  // Kết nối đến WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Cài đặt camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL;
  config.ledc_timer = LEDC_TIMER;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_brightness = -1;
  config.xclk_freq_hz = 20000000;
  config.ledc_channel = LEDC_CHANNEL;
  config.ledc_timer = LEDC_TIMER;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  if (!esp_camera_init(&config))
  {
    Serial.println("Camera init failed");
    return;
  }

  // Đặt route cho HTTP server
  server.on("/", HTTP_GET, []()
            {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      server.send(500, "text/plain", "Failed to capture image");
      return;
    }
    server.send_P(200, "image/jpeg", fb->buf, fb->len);
    esp_camera_fb_return(fb); });

  server.begin();
}

void loop()
{
  server.handleClient();
}
