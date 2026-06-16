

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
#define freq_l 18
#define t 300000
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




void setup(){

  //ponta de prova
  pinMode(pin_Low, INPUT_PULLUP); 
  pinMode(pin_High, INPUT_PULLUP); 
  pinMode(pin_F, INPUT_PULLUP); 
 
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



  //teste de frequencia
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
 
void loop() {
 
  int pulse = (pulseIn(freq_l, HIGH, t))*2;
  leitura = (1000000 / pulse); 
  if(leitura >= limite){
    digito = C;
  }
  else{
    high_stat = digitalRead(pin_Low);
    low_stat = digitalRead(pin_High);
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
  delay(100);
}
 
void ligaSegmentosDisplay(byte digito){ 
  for (byte i = 0; i < 6; ++i){ 
    digitalWrite(pin_BCD[i], displaySeteSeg[digito][i]);
  }
}