#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic
int trig = 2;
int echo = 3;
int duration, dist;
int threshold_distance = 5;

// Motor
int in1 = 9;
int in2 = 10;
int ena = 11;

// Potentiometer
int pot = A0;
int potValue, motorSpeed, targetSpeed;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

int calculateDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  // Read distance
  dist = calculateDistance(trig, echo);
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  //potentiometer control motorSpeed
  potValue = analogRead(pot);
  targetSpeed = map(potValue, 0, 1023, 0, 255);
  
  //conditions
  if( dist < 30 && dist > threshold_distance){
    motorSpeed -=5;
  }
  else if (dist <= threshold_distance){
    motorSpeed = 0;
  }
  else if(motorSpeed > targetSpeed){
    motorSpeed -=5;
  } 
  else if(motorSpeed < targetSpeed){
    motorSpeed +=5;
  }
  
  

  
  
  motorSpeed = constrain(motorSpeed, 0, 255);
  
  
  // Motor forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, motorSpeed);
  
  
  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Speed: ");
  lcd.print(motorSpeed);

  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  lcd.print(dist);
  lcd.print(" cm");

  delay(300);

}
