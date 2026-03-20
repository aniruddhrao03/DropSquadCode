// X-Axis: PB7 (OC1C) - Timer1
// Y-Axis: PH4 (OC4B) - Timer4
// Joystick X: A5 → controls X-Axis stepper
// Joystick Y: A4 → controls Y-Axis stepper
// DIR pin: pin 6

#define JOY_X A5
#define JOY_Y A4

// Direction pins — adjust to your wiring
#define DIR_X 12    // X-Axis DIR
#define DIR_Y 6   // Y-Axis DIR

#define DEADZONE 50

void setup() {
  // Direction pins as output
  // DIR_Y = pin 6 = PORTD bit 6
  DDRD |= (1<<6);
  PORTD &= ~(1<<6);

  // DIR_X = pin 12 = PORTB bit 6
  DDRB |= (1<<6);
  PORTB &= ~(1<<6);

  // X-Axis stepper — PB7 (OC1C)
  DDRB |= (1 << PB7);
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1A |= (1 << COM1C0);   // Toggle PB7 on match
  OCR1A   = 155;              // Speed — lower = faster

  // Y-Axis stepper — PH4 (OC4B)
  DDRH |= (1 << PH4);
  TCCR4A = 0;
  TCCR4B = 0;
  TCCR4B |= (1 << WGM42);    // CTC mode
  TCCR4A |= (1 << COM4B0);   // Toggle PH4 on match
  OCR4A   = 155;              // Speed — lower = faster

  // Both timers stopped until joystick moves
  // (no CS bits set yet)

  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void stopX() {
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}

void startX() {
  TCCR1B |= (1 << CS10);     // prescaler = 1
}

void stopY() {
  TCCR4B &= ~((1 << CS42) | (1 << CS41) | (1 << CS40));
}

void startY() {
  TCCR4B |= (1 << CS40);     // prescaler = 1
}

void loop() {
  int joyX = analogRead(JOY_X);  // 0–1023, center ~512
  int joyY = analogRead(JOY_Y);  // 0–1023, center ~512

  // --- X-AXIS STEPPER ---
  if (joyX > 512 + DEADZONE) {
    PORTD |= (1 << 6);   // DIR HIGH = forward
    startX();
  }
  else if (joyX < 512 - DEADZONE) {
    PORTD &= ~(1 << 6);  // DIR LOW = reverse
    startX();
  }
  else {
    stopX();             // Centered = stop
  }

  // --- Y-AXIS STEPPER ---
  if (joyY > 512 + DEADZONE) {
    digitalWrite(DIR_Y, HIGH);  // DIR HIGH = forward
    startY();
  }
  else if (joyY < 512 - DEADZONE) {
    digitalWrite(DIR_Y, LOW);
    startY();
  }
  else {
    stopY();             // Centered = stop
  }
}