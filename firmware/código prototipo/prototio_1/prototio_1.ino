

//-------------------------------------------
//PONTA DE PROVA
//-----------------------------------------
//-------------------------------------------
//definições para ponta de prova
//-----------------------------------------

#define pin_Low 17
#define pin_High 18
#define pin_F 19
int high_stat;
int low_stat;
int f_stat;

//-------------------------------------------
//definições para frequencimetro
//-----------------------------------------


long leitura; // cria a variável tipo long
#define freq_l 2
#define t 100000
#define limite 40

//-------------------------------------------
//definições para BCD
//-----------------------------------------

int digito; //

#define F 5
#define A 4
#define C 3
#define V 2
#define T 6
 
byte displaySeteSeg[7][7] = { 
 //to juntando a parte da direita, o b e o c
 { 1,1,1,1,1,0},  //DIGITO 0
 { 0,1,0,0,0,0},  //DIGITO 1
 { 0,0,0,0,0,0}, //vaziio
 { 1,0,1,1,1,0},    //C
 { 1,1,0,1,1,1},    //A
 { 1,0,0,1,1,1},    //F
 { 1,1,1,1,1,1}     //tudo 
};
 
int pin_BCD[6] = {16, 15, 12, 11, 13, 14};


//-------------------------------------------
//  CLOCK
//-----------------------------------------
//-------------------------------------------
//definições para frequencia output
//-----------------------------------------

//pino de interrupção
#define Interrupt_pin 3

//saida da frequencia
#define pin_100k 9
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
  Serial.begin(9600);

  //-------------------------------------------
  //PONTA DE PROVA
  //ponta de prova
  pinMode(pin_Low, INPUT_PULLUP); 
  pinMode(pin_High, INPUT_PULLUP); 
  pinMode(pin_F, INPUT_PULLUP); 
  pinMode(freq_l, INPUT_PULLUP); 
 
  //BCD
  pinMode(pin_BCD[0], OUTPUT);
  pinMode(pin_BCD[1], OUTPUT);
  pinMode(pin_BCD[2], OUTPUT);
  pinMode(pin_BCD[3], OUTPUT);
  pinMode(pin_BCD[4], OUTPUT);
  pinMode(pin_BCD[5], OUTPUT);

  //inicializa display vazio
  digito = V;
  ligaSegmentosDisplay(digito);


  //-------------------------------------------
  //CLOCK
  //---------------------------------
  //configurando pinos de frequencia
  pinMode(pin_10k, OUTPUT);
  pinMode(pin_1k, OUTPUT);
  pinMode(pin_100, OUTPUT);
  pinMode(pin_10, OUTPUT);
  pinMode(pin_1, OUTPUT);
  pinMode(pin_01, OUTPUT);

  //---------------------------------
  //configurando interrupção
  cli();
  pinMode(Interrupt_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(Interrupt_pin), freq, RISING); //RISING

  //---------------------------------
  //configurando frequencia 100k
  pinMode(pin_100k, OUTPUT); // OC1A no Arduino Uno/Nano
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
  sei();

}

void loop() {
    int pulse = (pulseIn(freq_l, HIGH, t))*2;
  leitura = (1000000 / pulse); 
  
  if(leitura >= limite){
    digito = C;
  }
  else{
    high_stat = digitalRead(pin_High);
    low_stat = digitalRead(pin_Low);
    f_stat = digitalRead(pin_F);

    if(high_stat == 1){
      digito = 1;
    }
    else if(low_stat == 1){
      digito = 0;
    }
    else if(f_stat == 1){
      digito = F;
    }
    else{
      digito = A;
    }
  }
  ligaSegmentosDisplay(digito);
}
 
void ligaSegmentosDisplay(byte digito){ 
  for (byte i = 0; i < 6; ++i){ 
    digitalWrite(pin_BCD[i], displaySeteSeg[digito][i]);
  }
}


//-------------------------------------------
//interrupção de tempo
//-----------------------------------------

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