// https://www.youtube.com/watch?v=7DwUOdvJp-8
// https://circuits.io/circuits/2707080
// https://gist.github.com/ulitiy/5c319f65c419dfa1af7ca2dcdebab3ce
#include <Servo.h>

Servo myservo;

const int servoPin = 9;
const int buttonPin = 12;
const int ledPin = 13;
const int feedUnits = 3;

void setup() {
  myservo.attach(servoPin);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  myservo.write(180);
  delay(1000);
  myservo.detach();
}

void loop() {
  int buttonVal = digitalRead(buttonPin);
  if(buttonVal == LOW) {
    feed(feedUnits);
  }
  delay(13);
}

void feed(int units) {
  for (int i = 0; i < units; i++) {
    feedOneUnit();
    delay(500);
  }
}

void feedOneUnit() {
  myservo.attach(servoPin);
  myservo.write(0);
  delay(400);
  myservo.write(180);
  delay(1500);
  myservo.detach();
}

