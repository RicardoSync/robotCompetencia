#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define MIN_PULSE_WIDTH 600
#define MAX_PULSE_WIDTH 2600
#define FREQUENCY 50

void setup() {
  Serial.begin(9600);  // Inicializa la comunicación serial a 9600 bps
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
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Leer hasta el salto de línea
    int separatorIndex = input.indexOf(',');  // Buscar el índice de la coma

    if (separatorIndex > 0) {
      String servoNumberStr = input.substring(0, separatorIndex);  // Extraer el número del servo
      String angleStr = input.substring(separatorIndex + 1);  // Extraer los grados

      int servoNumber = servoNumberStr.toInt();  // Convertir el número del servo a entero
      int angle = angleStr.toInt();  // Convertir los grados a entero

      if (servoNumber >= 0 && servoNumber < 16 && angle >= 0 && angle <= 180) {  // Validar entrada
        pwm.setPWM(servoNumber, 0, pulseWidth(angle));
        Serial.print("Servo: ");
        Serial.print(servoNumber);
        Serial.print(", Angle: ");
        Serial.println(angle);
      } else {
        Serial.println("Invalid input");
      }
    } else {
      Serial.println("Invalid format");
    }
  }
}
