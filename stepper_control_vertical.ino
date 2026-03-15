#include <Servo.h>

#define DIR_PIN 6   // ARM_Y_DIR_D6 → DIR- on TB6600
#define PUL_PIN 7   // ARM_Y_PWM_D7 → PUL- on TB6600
Servo servo;

const int btnA = 4;
const int btnB = 5;

int currentSpeed = 90;
const int rampDelay = 5;

void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUL_PIN, OUTPUT);
  digitalWrite(DIR_PIN, LOW);
  servo.attach(9);
  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);
  servo.write(90); 
}

void loop() {
  // --- STEPPER SPEED ---
  // Lower Microseconds = Faster Shaft Rotation
  digitalWrite(PUL_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(PUL_PIN, LOW);
  delayMicroseconds(10);

  // --- SERVO SPEED ---
  if (digitalRead(btnA) == LOW && currentSpeed < 180) {
    currentSpeed += 2;
    servo.write(currentSpeed);
    delay(rampDelay);
  } 

  if (digitalRead(btnB) == LOW && currentSpeed > 0) {
    currentSpeed -= 2; 
    servo.write(currentSpeed);
    delay(rampDelay);
  } 
}