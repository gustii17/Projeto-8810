long leitura; // cria a variável tipo long
#define freq_l 3
#define t 300000

void setup()
{
  Serial.begin(9600); //inicia o serial
  pinMode(freq_l, INPUT_PULLUP); // define o pino 6 como entrada

  //frequencia teste (10k):
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
  TCCR1B |= (1 << CS11);
  //OCR1A
  OCR1A = 99;

}
void loop()
{
  int pulse = (pulseIn(freq_l, HIGH, t))*2;
  leitura = (1000000 / pulse); 
  delay(200);
   Serial.print("pulse: ");
  Serial.println(pulse); 
  Serial.print("Frequência (Hz): "); //escreve no monitor serial
  Serial.println(leitura); //escreve o valor de leitura, que é em hertz
}