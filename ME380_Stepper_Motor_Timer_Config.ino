void setup()
{
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);

  // FOR STEPPER DRIVER TIMER CONFIGURATIONS
    // ----- 1. Set pins as outputs -----
    DDRB |= (1<<PB7);   // PB7 (OC1C) output for X-Axis Stepper
    DDRH |= (1<<PH4);   // PH4 (OC4B) output for Y-Axis Stepper

    // ----- 2. Clear timer control registers -----
    TCCR1A = 0;
    TCCR1B = 0;

    TCCR4A = 0;
    TCCR4B = 0;

    // ----- 3. Enable CTC mode with OCRnA as TOP -----
    // Timer1 Mode 4
    TCCR1B = (1 << WGM12); 
    TCCR1A = 0;

    // Timer4 Mode 4
    TCCR4B = (1 << WGM42);
    TCCR4A = 0;

    // ----- 4. Toggle output pins on compare match -----
    TCCR1A |= (1<<COM1C0);  // Toggle PB7 (OC1C)
    TCCR4A |= (1<<COM4B0);  // Toggle PH4 (OC4B)

    // ----- 5. Set TOP/compare values -----
    // SET THESE TO VALUE BETWEEN 0 AND 65535 TO SET MOTOR SPEEDS. OCR4A SETS Y-AXIS SPEED, OCR1A SETS X-AXIS SPEED. 155 SETS SPEED TO 4 RPS
    OCR1A = 155;   // Timer1: PB7 TOP value
    OCR4A = 155;   // Timer4: PH4 TOP value

    // ----- 6. Start timers with prescaler = 1 -----
    TCCR1B |= (1<<CS10);    // Timer1 prescaler = 1
    TCCR4B |= (1<<CS40);    // Timer4 prescaler = 1
    // END OF STEPPER DRIVER TIMER CONFIGURATIONS
}

void loop()
{
    // Enable Motion of Y-Axis Stepper
    // TCCR4B |= (1 << CS40);  // CS42=0, CS41=0, CS40=1 → clk/1

    // Disable Motion of Y-Axis Stepper
    // TCCR4B &= ~((1<<CS42)|(1<<CS41)|(1<<CS40));  // All CS bits 0 → timer stops
  
    // Enable Motion of X-Axis Stepper
    // TCCR1B |= (1 << CS10);

    // Disable Motion of X-Axis Stepper
    // TCCR1B &= ~((1<<CS12)|(1<<CS11)|(1<<CS10));
}