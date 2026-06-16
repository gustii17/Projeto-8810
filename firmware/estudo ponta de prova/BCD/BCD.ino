
int digito; //

#define F 4
#define A 3
#define C 2
 
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
 
int pin_BCD[6] = {16, 15, 11, 12, 14, 13};

void setup(){
  Serial.begin(9600);
 
  //Definindo pinos como saída
  pinMode(pin_BCD[0], OUTPUT);
  pinMode(pin_BCD[1], OUTPUT);
  pinMode(pin_BCD[2], OUTPUT);
  pinMode(pin_BCD[3], OUTPUT);
  pinMode(pin_BCD[4], OUTPUT);
  pinMode(pin_BCD[5], OUTPUT);
 
  //inicializa display com número 0
  digito = 0;
  ligaSegmentosDisplay(digito);
   
}
 
void loop() {
  digito++;
  delay(1000);
  ligaSegmentosDisplay(digito);
  Serial.println(digito);
  if(digito >= 6){
    digito = -1;

  } 
}
 
void ligaSegmentosDisplay(byte digito){ 
  for (byte i = 0; i < 6; ++i){ 
    digitalWrite(pin_BCD[i], displaySeteSeg[digito][i]);
  }
}