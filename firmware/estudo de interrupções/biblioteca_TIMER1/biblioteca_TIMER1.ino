#include <TimerOne.h>

int pin = 13;
int ledState = LOW;

void setup() {
  pinMode(pin, OUTPUT);
  Timer1.initialize(500000); //periodo para low ou para high, da meio que o dobro do periodo
  Timer1.attachInterrupt(pisca_led);
}

void pisca_led(void){
  if(ledState == HIGH) {
    ledState = LOW;
  } 
  else{
    ledState = HIGH;
  } 
  digitalWrite(pin, ledState);
}

// Loop infinito: acende, espera, apaga e espera
void loop() {
 
}

//timer1.detachInterupt - desabilita
//timer1.read - ler
//noInterupt()/Interrupt()
//variaveir compartilhadas devem ser: volatile unsigned long
