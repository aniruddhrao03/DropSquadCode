#include <Servo.h>

// =========================
// PIN DEFINITIONS
// =========================
#define DIR_H        12   // Horizontal DIR (PB6)
#define DIR_Y        6    // Y-Axis DIR
#define PUL_H        13   // Horizontal PUL (PB7)
#define PUL_Y        7    // Y-Axis PUL (PH4)
#define JOY_Y        A4   // Joystick Y axis
#define JOY_X        A5   // Joystick X axis

Servo servo;
const int btnA = 4;
const int btnB = 5;
int currentSpeed = 90;
const int rampDelay = 5;

void setup() {
  pinMode(DIR_H, OUTPUT);
  pinMode(DIR_Y, OUTPUT);
  pinMode(PUL_H, OUTPUT);
  pinMode(PUL_Y, OUTPUT);
  digitalWrite(DIR_H, LOW);
  digitalWrite(DIR_Y, LOW);

  servo.attach(9);
  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);
  servo.write(90);
}

void loop() {
  int joyY     = analogRead(JOY_Y);
  int joyX     = analogRead(JOY_X);
  int deadLow  = 470;
  int deadHigh = 550;

  // =========================
  // JOYSTICK Y -> Y-AXIS STEPPER
  // =========================
  if (joyY > deadHigh) {
    digitalWrite(DIR_Y, HIGH);
    int pulseDelay = map(joyY, deadHigh, 1023, 1200, 200);
    pulseDelay = constrain(pulseDelay, 200, 1200);
    digitalWrite(PUL_Y, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(PUL_Y, LOW);
    delayMicroseconds(pulseDelay);
  }
  else if (joyY < deadLow) {
    digitalWrite(DIR_Y, LOW);
    int pulseDelay = map(joyY, 0, deadLow, 200, 1200);
    pulseDelay = constrain(pulseDelay, 200, 1200);
    digitalWrite(PUL_Y, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(PUL_Y, LOW);
    delayMicroseconds(pulseDelay);
  }
  // else: center = stop, no pulse

  // =========================
  // JOYSTICK X -> HORIZONTAL STEPPER
  // =========================
  if (joyX > deadHigh) {
    digitalWrite(DIR_H, HIGH);
    int pulseDelay = map(joyX, deadHigh, 1023, 1200, 200);
    pulseDelay = constrain(pulseDelay, 200, 1200);
    digitalWrite(PUL_H, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(PUL_H, LOW);
    delayMicroseconds(pulseDelay);
  }
  else if (joyX < deadLow) {
    digitalWrite(DIR_H, LOW);
    int pulseDelay = map(joyX, 0, deadLow, 200, 1200);
    pulseDelay = constrain(pulseDelay, 200, 1200);
    digitalWrite(PUL_H, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(PUL_H, LOW);
    delayMicroseconds(pulseDelay);
  }
  // else: center = stop, no pulse

  // =========================
  // BUTTONS -> SERVO CONTROL
  // =========================
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