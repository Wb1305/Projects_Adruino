#include <Arduino.h>

#define LED 4

const int freq = 5000;
const int resolution = 8;
const int channel = 0;

void setup()
{
  // put your setup code here, to run once:
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(LED, channel);
}

void loop()
{
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 255; i++)
  {
    ledcWrite(channel, i);
    delay(500);
  }
  for (int i = 255; i >= 0; i--)
  {
    ledcWrite(channel, i);
    delay(500);
  }
}
