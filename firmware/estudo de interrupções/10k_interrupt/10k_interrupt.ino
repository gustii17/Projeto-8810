

//-------------------------------------------
//definições para frequencimetro
//-----------------------------------------

//pino de interrupção
#define Interrupt_pin 3

//saida da frequencia
#define pin_10k 4
int cont_1k = 5; 
#define pin_1k 5
int cont_100 = 10; 
#define pin_100 6
int cont_10 = 10; 
#define pin_10 7
int cont_1 = 10; 
#define pin_1 8
int cont_01 = 10; 
#define pin_01 10 

void setup() {

  
  //pinos de frequencia
  pinMode(pin_10k, OUTPUT);
  pinMode(pin_1k, OUTPUT);
  pinMode(pin_100, OUTPUT);
  pinMode(pin_10, OUTPUT);
  pinMode(pin_1, OUTPUT);
  pinMode(pin_01, OUTPUT);


  //pino da interrupção como INPUT
  cli();
  pinMode(Interrupt_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(Interrupt_pin), freq, RISING); //RISING
  
  //A0 OUTPUT
  DDRC |= (1<<DDC0);
  PORTC |= (1<<PC0);

  
  //configurando a frequencia 10k
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

    
  
  sei();
}

void loop() {
  
  PORTC |= (1<<PC0);
  delay(1);
  PORTC &= ~(1<<PC0);
  delay(1);
  
}

//posso testar com change, mas qualquer coisa eu pego do pino no propio coiso para deixar mais rapido
void freq(){
  PORTD ^= (1<<PD4);
  
  if(--cont_1k == 0){
    PORTD ^= (1<<PD5);
    cont_1k = 5;
      
    if(--cont_100 == 0){
      PORTD ^= (1<<PD6);
      cont_100 = 10;
      
      if(--cont_10 == 0){
        PORTD ^= (1<<PD7);
        cont_10 = 10;

        if(--cont_1 == 0){
          PORTB ^= (1<<PB0);
          cont_1 = 10;

          if(--cont_01 == 0){
            PORTB ^= (1<<PB2);
            cont_01 = 10;
          } 
        }
      }
    
    }
  }
  
  
}