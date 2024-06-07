#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define MIN_PULSE_WIDTH 600
#define MAX_PULSE_WIDTH 2600
#define FREQUENCY 50

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}

int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

void loop() {
  pwm.setPWM(0, 0, pulseWidth(0));
  pwm.setPWM(1, 0, pulseWidth(180));
  delay(1000);
  pwm.setPWM(4, 0, pulseWidth(0));
  delay(1000);
  pwm.setPWM(0, 0, pulseWidth(180));
  pwm.setPWM(1, 0, pulseWidth(90));
  delay(500);
  pwm.setPWM(4, 0, pulseWidth(180));
  delay(1000);
  pwm.setPWM(0, 0, pulseWidth(90));
  pwm.setPWM(1, 0, pulseWidth(0));
  delay(1000);
}
