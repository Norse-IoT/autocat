/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ds1307-rtc-module
 */

#include <RTClib.h>
#include <TimeAlarms.h>  // needs TimeAlarms@1.5 by Michael Margolis
// depends on Time@1.6.1 by Michael Margolis

const int relay_pin = 10;  // digital pin 10 on Arduino Nano

RTC_DS1307 rtc;

void setup() {
  pinMode(relay_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  // SETUP RTC MODULE
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1)
      ;
  }
  // set rtc to compile time.
  // Note that this line should be used once, then removed, lest the RTC chip be overwritten if the Arduino loses power.
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Set initial time for TimeAlarms
  DateTime now = rtc.now();
  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());

  // Based on my measurements, 10 minutes on = 1 cup of food.
  // This should use 3 cups of food per day.

  // Morning (8am) - 2 cups
  Alarm.alarmRepeat(8, 0, 0, turnOn);
  Alarm.alarmRepeat(8, 20, 0, turnOff);

  // Evening (5pm) - 1 cup
  Alarm.alarmRepeat(17, 0, 0, turnOn);
  Alarm.alarmRepeat(17, 10, 0, turnOff);

  testMotor();
}

void loop() {
  DateTime now = rtc.now();
  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());

  Alarm.delay(100);  // check & trigger alarms
}

void turnOn() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(relay_pin, HIGH);
}

void turnOff() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(relay_pin, LOW);
}

void testMotor() {
  turnOn();
  delay(10 * 1000);  // 10 seconds
  turnOff();
}
