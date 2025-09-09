//
const int flash_button = 2;
const int turnOff_button = 3;
const int led = 13;
int b1 , b2;

void setup() {
  pinMode(flash_button, INPUT_PULLUP);
  pinMode(turnOff_button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  b1 = digitalRead(flash_button);
  b2 = digitalRead(turnOff_button);

  if ( b1 == LOW){
    digitalWrite(led,HIGH);
  }
  else if( b2 == LOW){
    digitalWrite(led,LOW);
  }
  else{
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
  }
    
}
