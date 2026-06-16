void setup() {
  // put your setup code here, to run once:]
    //A0 OUTPUT
  DDRC |= (1<<DDC0);
  PORTC |= (1<<PC0);

  

}

void loop() {
  // put your main code here, to run repeatedly:
  PORTC |= (1<<PC0);
  delay(1);
  PORTC &= ~(1<<PC0);
  delay(1);
}
