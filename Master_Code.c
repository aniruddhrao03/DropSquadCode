#include <Servo.h>
#define DIR_PIN 2
#define PUL_PIN 3

Servo servo;

const int btnA = 4;
const int btnB =5;

int currentSpeed = 90; // Start at stop (90)
const int maxSpeed = 180; // Full speed
const int rampDelay = 20; // Increase this number to ramp up SLOWER

void setup() {

  pinMode(DIR_PIN, output);
  pinMode(PUL_PIN)
  digitalWrite(DIR_PIN, HIGH);

  servo.attach(9);
  pinMode(btnA, INPUT_PULLUP);
  servo.write(90); 
}

void loop() {

  digitalWirte(PUL_PIN, HIGH);
  delayMicroseconds(200);
  digitalWrite(PUL_PIN, LOW);
  delayMicroseconds(200);

  if (digitalRead(btnA) == LOW) {
    // If button is held and we haven't reached max speed yet
    if (currentSpeed < maxSpeed) {
      currentSpeed++; // Increment speed by 1
      servo.write(currentSpeed);
      delay(rampDelay); // Wait a bit so it doesn't hit max speed instantly
    }
  } 

  if (digitalRead(btnB) == LOW) {
    // If button is held and we haven't reached max speed yet
    if (currentSpeed < maxSpeed) {
      currentSpeed--; // Decrement speed by 1
      servo.write(currentSpeed);
      delay(rampDelay); // Wait a bit so it doesn't hit max speed instantly
    }
  } 
  
}