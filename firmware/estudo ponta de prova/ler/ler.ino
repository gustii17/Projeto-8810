#define pin_Low 17
#define pin_High 18
#define pin_F 19
int high_stat;
int low_stat;
int f_stat;


void setup() {
  Serial.begin(9600); //inicia o serial
  pinMode(pin_Low, INPUT_PULLUP); 
  pinMode(pin_High, INPUT_PULLUP); 
  pinMode(pin_F, INPUT_PULLUP); 

}

void loop() {
  high_stat = digitalRead(pin_Low);
  low_stat = digitalRead(pin_High);
  f_stat = digitalRead(pin_F);

  if(high_stat == 1){
    Serial.println("1");
  }
  else if(low_stat == 1){
    Serial.println("0");
  }
  else if(f_stat == 1){
    Serial.println("F");
  }
  else{
    Serial.println("A");
  }
  delay(200);
}
