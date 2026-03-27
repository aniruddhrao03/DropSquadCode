#include <Servo.h>

#define Y_DIR 6
#define X_DIR 12
#define TURN_DIR 2
#define BTN_UP        31   // Joystick Y axis
#define BTN_DOWN      30
#define JOY_X         A5   // Joystick X axis
#define JOY_Y         A4
#define BTN_GRAB      40
#define BTN_REL       41

// DEFINE FUNCTION PROTOTYPES

Servo grabber;
void y_start()
{
  //STARTS TIMER 4 OUTPUT to OC4B PIN PH4
  TCCR4B |= (1 << CS41);  // PRESCALAR 8
}

void y_stop() {
  // ENDS TIMER 4 OUTPUT TO OC4B PIN PH4
  TCCR4B &= ~((1<<CS42)|(1<<CS41)|(1<<CS40));  // All CS bits 0 → timer stops
}

void turn_start() {
  TCCR3B |= (1 << CS31);  // PRESCALAR 8
}

void turn_stop() {
  TCCR3B &= ~((1<<CS32)|(1<<CS31)|(1<<CS30));  // All CS bits 0 → timer stops
}

void x_start() {
    // STARTS TIMER 1 OUTPUT TO OC1C PIN PB7
    TCCR1B |= (1 << CS11); // PRESCALAR 8
}

void x_stop() {

    // ENDS TIMER 1 OUTPUT TO OC1C PIN PB7
    TCCR1B &= ~((1<<CS12)|(1<<CS11)|(1<<CS10));
}

void setup()
{
  Serial.begin(9600);
  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DOWN, INPUT);
  
  pinMode(Y_DIR, OUTPUT);
  digitalWrite(Y_DIR, LOW);

  pinMode(X_DIR, OUTPUT);
  digitalWrite(X_DIR, LOW);

  pinMode(TURN_DIR, OUTPUT);
  digitalWrite(TURN_DIR, LOW);

  pinMode(BTN_GRAB, INPUT);
  pinMode(BTN_REL, INPUT);

  // FOR STEPPER DRIVER TIMER CONFIGURATIONS
    // ----- 1. Set pins as outputs -----
    DDRB |= (1<<PB7);   // PB7 (OC1C) output for X-Axis Stepper
    DDRH |= (1<<PH4);   // PH4 (OC4B) output for Y-Axis Stepper
    DDRE |= (1<<PE5);   // PE5 (OC3C) output for Turntable Stepper

    // ----- 2. Clear timer control registers -----
    TCCR1A = 0;
    TCCR1B = 0;

    TCCR3A = 0;
    TCCR3B = 0;

    TCCR4A = 0;
    TCCR4B = 0;

    // ----- 3. Enable CTC mode with OCRnA as TOP -----
    // Timer1 Mode 4
    TCCR1B = (1 << WGM12); 
    TCCR1A = 0;

    // Timer3 Mode 3
    TCCR3B = (1 << WGM32); 
    TCCR3A = 0;

    // Timer4 Mode 4
    TCCR4B = (1 << WGM42);
    TCCR4A = 0;

    // ----- 4. Toggle output pins on compare match -----
    TCCR1A |= (1<<COM1C0);  // Toggle PB7 (OC1C)
    TCCR3A |= (1<<COM3C0);  // Toggle PE5 (OC3C) 
    TCCR4A |= (1<<COM4B0);  // Toggle PH4 (OC4B)

    // ----- ESE TO VALUE BETWEEN 0 AND 65535 TO SET MOTOR SPEEDS. OCR4A SETS Y-AXIS SPEED, OCR1A SETS X-AXIS SPEED. 155 SETS SPEED TO 4 RPS
    OCR1A = 155;   // Timer1: PB7 TOP value
    OCR3A = 1249;  // Timer3: PE5 TOP value
    OCR4A = 155;   // Timer4: PH4 TOP value

    /* ----- 6. Start timers with prescaler = 1 -----
    TCCR1B |= (1<<CS11);    // Timer1 prescaler = 8
    TCCR4B |= (1<<CS41);    // Timer4 prescaler = 8
    END OF STEPPER DRIVER TIMER CONFIGURATIONS
    */
    grabber.attach(9);
    grabber.write(90); 
}

void loop()
{
  // Define deadzones for joystick and grab current value reading
  int joystick_Y_state = analogRead(JOY_Y);
  int joystick_X_state = analogRead(JOY_X);
  int deadLow  = 470;
  int deadHigh = 550;
  int button_up_state = digitalRead(BTN_UP);
  int button_down_state = digitalRead(BTN_DOWN);
  bool btn_grab_status = digitalRead(BTN_GRAB);
  bool btn_rel_status = digitalRead(BTN_REL);

while(button_up_state == 0 || button_down_state == 0) {
  if(button_up_state == 0) {
    digitalWrite(TURN_DIR, HIGH);
    }
  if(button_up_state == 0) {
    digitalWrite(TURN_DIR,LOW);
    }
  turn_start();
  button_up_state = digitalRead(BTN_UP);
  button_down_state = digitalRead(BTN_DOWN);
  }

while(joystick_Y_state > deadHigh || joystick_Y_state < deadLow) {
  if(joystick_Y_state > deadHigh) {
    digitalWrite(Y_DIR, LOW);
  }
  else if (joystick_Y_state < deadLow) {
    digitalWrite(Y_DIR, HIGH);
  }
  y_start();
  joystick_Y_state = analogRead(JOY_Y); 
}

while(joystick_X_state > deadHigh || joystick_X_state < deadLow) {
  if(joystick_X_state > deadHigh) {
    digitalWrite(X_DIR, LOW);
  }
  else if (joystick_X_state < deadLow) {
    digitalWrite(X_DIR, HIGH);
  }
  x_start();
  joystick_X_state = analogRead(JOY_X); 
}

if(btn_grab_status == 0) {
    grabber.write(0); 
}
if(btn_rel_status == 0) {
    grabber.write(180); 
}
turn_stop();
y_stop();
x_stop();

}

