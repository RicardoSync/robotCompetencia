#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);


#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

void setup() {
  Serial.begin(9600);
  Serial.println("32 channel Servo test!");

  board1.begin();
  board2.begin();  
  board1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  board2.setPWMFreq(60);
}

void loop() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the servo number
    int servoNumber = Serial.parseInt();
    // Read the angle
    int angle = Serial.parseInt();
    
    // Check if servo number and angle are valid
    if (servoNumber >= 0 && servoNumber < 32 && angle >= 0 && angle <= 180) {
      // Determine which board to use
      if (servoNumber < 16) {
        board1.setPWM(servoNumber, 0, angleToPulse(angle));
      } else {
        board2.setPWM(servoNumber - 16, 0, angleToPulse(angle));
      }
      // Print the servo number and angle for debugging
      Serial.print("Servo: ");
      Serial.print(servoNumber);
      Serial.print(" Angle: ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid servo number or angle");
    }
  }
}


int angleToPulse(int ang){
   int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");
   Serial.print(ang);
   Serial.print(" pulse: ");
   Serial.println(pulse);
   return pulse;
}
