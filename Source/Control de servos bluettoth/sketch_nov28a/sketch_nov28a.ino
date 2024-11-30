#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <BluetoothSerial.h>

// Llamamos a las placas, con las direcciones predeterminadas 0x40 y 0x41
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);

BluetoothSerial SerialBT;  // Crear objeto de Bluetooth Serial

#define SERVOMIN  125 // Este es el valor mínimo del pulso (de 0 a 4095)
#define SERVOMAX  575 // Este es el valor máximo del pulso (de 0 a 4095)

// Función para convertir el ángulo a un valor de pulso
int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);  // Convertimos el ángulo de 0-180 a un valor de pulso
  Serial.print("Angle: ");
  Serial.print(ang);
  Serial.print(" pulse: ");
  Serial.println(pulse);
  return pulse;
}

void setup() {
  Serial.begin(9600);  // Inicializamos el puerto serie para depuración por USB
  SerialBT.begin("ESP32_Servo_Controller");  // Nombre del dispositivo Bluetooth

  Serial.println("ESP32 Bluetooth Servo Test!");

  board1.begin();
  board2.begin();  
  board1.setPWMFreq(60);  // Los servos analógicos funcionan a ~60 Hz de frecuencia de actualización
  board2.setPWMFreq(60);

  Serial.println("Esperando conexión Bluetooth...");
}

// Función para ajustar servos a posiciones específicas
void statica() {
  board1.setPWM(15, 0, angleToPulse(110));
  board1.setPWM(14, 0, angleToPulse(140));
  board1.setPWM(13, 0, angleToPulse(55));
  board1.setPWM(12, 0, angleToPulse(70));
  board1.setPWM(11, 0, angleToPulse(115));
  board1.setPWM(4, 0, angleToPulse(150));
  board1.setPWM(3, 0, angleToPulse(100));
  board1.setPWM(2, 0, angleToPulse(160));
  board1.setPWM(1, 0, angleToPulse(140));
  board1.setPWM(0, 0, angleToPulse(85));
  
  // Enviar mensaje por Bluetooth
  SerialBT.println("Posición huevos establecida");
  
  // Mensaje para depuración
  Serial.println("Función statica ejecutada: servos ajustados.");
}

void manoDerecha() {
  // hombro (servo 5): mueve hacia adelante (elevación del brazo)
  board1.setPWM(5, 0, angleToPulse(120)); // Ajusta el ángulo para mover el hombro hacia enfrente
  delay(500);
  // brazo (servo 6): ajusta el brazo para alinear con el hombro
  board1.setPWM(6, 0, angleToPulse(135)); // Ajusta según la posición deseada
  delay(500);
  // antebrazo (servo 7): mantén el antebrazo recto o en un ángulo específico
  board1.setPWM(7, 0, angleToPulse(100)); // Recto o ajustado hacia adelante
  delay(500);
  // Enviar mensaje por Bluetooth
  SerialBT.println("Mano derecha ajustada hacia enfrente");
}

void golpearDerecha(){
  board1.setPWM(6, 0, angleToPulse(90));
  SerialBT.println("Golpe derecho asestado");
}


void loop() {
  // Verificamos si hay datos disponibles por Bluetooth
  if (SerialBT.available() > 0) {
    String input = SerialBT.readStringUntil('\n');  // Lee el comando como String
    input.trim();  // Elimina espacios y caracteres como '\n' o '\r'
    
    if (input == "1") {  // Compara con el comando "1"
      manoDerecha();
    } else if (input == "0") {  // Comando para función statica
      statica();
    } else if (input == "2") {
      golpearDerecha();
    } else {
      SerialBT.println("Comando no reconocido");
    }
  }
}

