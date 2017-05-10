/**
 * CAT FEEDER
 * 
 * A way to automate pet feed.
 * 
 * Configuration:
 * Servo:
 * - Red: 5v
 * - Black: Ground
 * - White: PIN_SERVO_AUTO_FEED
 * Clock:
 * - SDA (right side): A4
 * - SCL (right side): A5
 * 
 * Links:
 * https://www.youtube.com/watch?v=7DwUOdvJp-8
 * https://circuits.io/circuits/2707080
 * https://gist.github.com/ulitiy/5c319f65c419dfa1af7ca2dcdebab3ce
 * https://www.pjrc.com/teensy/td_libs_TimeAlarms.html
 */
 
#include <Servo.h>
#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

Servo myservo;

const int PIN_SERVO_AUTO_FEED = 9;
const int DEFAULT_AUTO_FEED_UNITS = 2;

const bool SHOW_LOG = true;

bool feeding = false;

void setup() {
  if (SHOW_LOG) {
    Serial.begin(9600);
  }
  setupClock();
  setupServo();
}

void loop() {
  if (SHOW_LOG) {
    digitalClockDisplay();
  }
  Alarm.delay(1000);
}

// SETUPS

void setupClock() {
  setTime(07, 29, 50, 10, 2, 17);
  Alarm.alarmRepeat(07, 30, 0, morningAlarm);
  Alarm.alarmRepeat(07, 30, 30, afternoonAlarm);
  Alarm.alarmRepeat(07, 31, 0, nightAlarm);
}

void setupServo() {
  myservo.attach(PIN_SERVO_AUTO_FEED);
  myservo.write(180);
  delay(1000);
  myservo.detach();
}

// ALARMS

void digitalClockDisplay() {
  // digital clock display of the time
  showLog(String(hour()) + timeDigitToString(minute()) + timeDigitToString(second()));
}

void morningAlarm() {
  showLog("morningAlarm"); 
  feed(DEFAULT_AUTO_FEED_UNITS);
}

void afternoonAlarm() {
  showLog("afternoonAlarm"); 
  feed(DEFAULT_AUTO_FEED_UNITS);
}

void nightAlarm() {
  showLog("nightAlarm"); 
  feed(DEFAULT_AUTO_FEED_UNITS);
}

// FEED

void feed(int units) {
  showLog("About to feed " + String(units) + " units");
  for (int i = 0; i < units; i++) {
    feedOneUnit();
    delay(500);
  }
}

void feedOneUnit() {
  if (feeding) {
    showLog("Invalid feed. It is actually feeding");
    return;
  }
  showLog("Feeding...");
  feeding = true;
  myservo.attach(PIN_SERVO_AUTO_FEED);
  myservo.write(0);
  delay(400);
  myservo.write(180);
  delay(1500);
  myservo.detach();
  feeding = false;
}

// UTILS

String timeDigitToString(int digits) {
  String digitsStr = ":";
  if (digits < 10) {
    digitsStr += "0";
  }
  digitsStr += digits;
  return digitsStr;
}

void showLog(String message) {
  if (SHOW_LOG) {
    Serial.println(message);
  }
}

