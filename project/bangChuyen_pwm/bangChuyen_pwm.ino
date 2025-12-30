#include<Arduino.h>
#include <ESP32Servo.h>

#define ENA 12
#define IN1 14
#define IN2 27
#define POT_PIN 13 // Chân analog đọc giá trị từ biến trở
#define SERVO_PIN 17

const int freq = 5000;
const int resolution = 8;
const int channel = 0;

Servo servo1;
bool isServo1Active = false;

void setup() {
  // Khởi động Serial để kiểm tra giá trị đọc được từ biến trở (tuỳ chọn)
  Serial.begin(115200);
  // Thiết lập các chân điều khiển động cơ là OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Thiết lập chân biến trở là INPUT
  pinMode(POT_PIN, INPUT);
  
  //pwm
  ledcAttachChannel(ENA, freq, resolution, channel);

  //servo1
  servo1.attach(SERVO_PIN, 500, 2500);

}

void loop() {
  controlMotor();
  controlServo1();
  // Thêm một khoảng delay nhỏ để cập nhật giá trị liên tục
  delay(10);
}

void controlMotor(){
// Đọc giá trị từ biến trở (trên ESP32, giá trị trả về từ 0 đến 4095)
  int potValue = analogRead(POT_PIN);
  
  // In ra giá trị đọc được để kiểm tra (tuỳ chọn)
  Serial.println(potValue);
  
  // Chuyển đổi giá trị từ biến trở sang giá trị PWM (từ 0 đến 255)
  int speed = map(potValue, 0, 4095, 0, 255);
  
  // Điều khiển động cơ DC
  ledcWriteChannel(channel, speed); // Điều chỉnh tốc độ động cơ thông qua PWM
  digitalWrite(IN1, HIGH);  // Đặt hướng quay cho động cơ (có thể đảo chiều)
  digitalWrite(IN2, LOW);   // Đặt hướng quay cho động cơ (có thể đảo chiều)
}

void controlServo1(){
  if(!isServo1Active){
    servo1.write(90);
    delay(1000);
    servo1.write(0);
  }
  else {
    servo1.write(0);
  }
}
