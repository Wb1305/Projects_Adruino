#include <Arduino.h>

#define LED 4

const int freq = 5000;
const int resolution = 8;
const int channel = 0;

void setup() {
  // Sử dụng ledcAttach để thiết lập kênh LEDC
  ledcAttachChannel(LED, freq, resolution, channel);
}

void loop() {
  // Tăng dần độ sáng của LED
  for(int i = 0; i <= 255; i++){
    ledcWriteChannel(channel, i);
    delay(20);
  }
  
  // Giảm dần độ sáng của LED
  for(int i = 255; i >= 0; i--){
    ledcWriteChannel(channel, i);
    delay(20);
  }
}
