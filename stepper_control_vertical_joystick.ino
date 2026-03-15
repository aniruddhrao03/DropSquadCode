#include <Servo.h>

#define DIR_PIN 6    // DIR- on TB6600
#define PUL_PIN 7    // PUL- on TB6600
#define JOY_X   A5   // Joystick X axis
#define JOY_Y   A4   // Joystick Y axis

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
  int joyX = analogRead(JOY_X);  // 0–1023, center ~512
  int joyY = analogRead(JOY_Y);  // 0–1023, center ~512

  // --- STEPPER (Y axis → direction + run/stop) ---
  if (joyY > 600) {
    digitalWrite(DIR_PIN, HIGH);   // Forward
    digitalWrite(PUL_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(PUL_PIN, LOW);
    delayMicroseconds(5);
  } 
  else if (joyY < 400) {
    digitalWrite(DIR_PIN, LOW);    // Reverse
    digitalWrite(PUL_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(PUL_PIN, LOW);
    delayMicroseconds(5);
  }
  // // else: centered → stepper stops

  // // --- SERVO (X axis → position) ---
  // int servoTarget = map(joyX, 0, 1023, 0, 180);

  // if (servoTarget > currentSpeed) {
  //   currentSpeed += 2;
  // } else if (servoTarget < currentSpeed) {
  //   currentSpeed -= 2;
  // }

  // // Buttons still work as manual override
  // if (digitalRead(btnA) == LOW && currentSpeed < 180) {
  //   currentSpeed += 2;
  // }
  // if (digitalRead(btnB) == LOW && currentSpeed > 0) {
  //   currentSpeed -= 2;
  // }

  // servo.write(currentSpeed);
  // delay(rampDelay);
}