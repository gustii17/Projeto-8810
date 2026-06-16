void setup() {
  pinMode(9, OUTPUT); // OC1A no Arduino Uno/Nano

  // Zera os registradores do Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Modo CTC: conta até OCR1A e reinicia
  TCCR1B |= (1 << WGM12);

  // Toggle automático do pino OC1A, que é o D9
  TCCR1A |= (1 << COM1A0);

  // Sem prescaler: clock do timer = 16 MHz
  TCCR1B |= (1 << CS10);

  //OCR1A
  OCR1A = 79;

  // Fórmula:
  // f = F_CPU / (2 * prescaler * (1 + OCR1A))
  //
  // 100000 = 16000000 / (2 * 1 * (1 + OCR1A))
  // OCR1A = 79

}

void loop() {
}