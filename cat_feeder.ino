// https://www.youtube.com/watch?v=7DwUOdvJp-8
// https://circuits.io/circuits/2707080
// https://gist.github.com/ulitiy/5c319f65c419dfa1af7ca2dcdebab3ce
#include <Servo.h>

Servo myservo;

const int SERVO_PIN = 9;
const int BUTTON_PIN = 12;
const int LED_PIN = 13;
const int DEFAULT_FEED_UNITS = 3;

void setup() {
  setupServo();
  setupClock();
}

void loop() {
  int buttonVal = digitalRead(BUTTON_PIN);
  if(buttonVal == LOW) {
    feed(DEFAULT_FEED_UNITS);
  }
  delay(13);
}

// SETUPS

void setupServo() {
  myservo.attach(SERVO_PIN);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  myservo.write(180);
  delay(1000);
  myservo.detach();
}

void setupClock() {
  setTime(7, 29, 0, 10, 2, 17); 
  Alarm.alarmRepeat(7, 30, 0, morningAlarm);
  Alarm.alarmRepeat(15, 00, 0, afternoonAlarm);
  Alarm.alarmRepeat(23, 30, 0, nightAlarm);
}

// ALARMS

void morningAlarm() {
  feed(DEFAULT_FEED_UNITS);
}

void afternoonAlarm() {
  feed(DEFAULT_FEED_UNITS);
}

void nightAlarm() {
  feed(DEFAULT_FEED_UNITS);
}

// FEED

void feed(int units) {
  for (int i = 0; i < units; i++) {
    feedOneUnit();
    delay(500);
  }
}

void feedOneUnit() {
  myservo.attach(SERVO_PIN);
  myservo.write(0);
  delay(400);
  myservo.write(180);
  delay(1500);
  myservo.detach();
}

