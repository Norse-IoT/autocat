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
  // set rtc to compile time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Set initial time for TimeAlarms
  DateTime now = rtc.now();
  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());

  // Based on my measurements, 15 minutes on = 1 cup of food.
  // This should use 2 cups of food per day.

  // Morning (8am)
  Alarm.alarmRepeat(8, 0, 0, turnOn);
  Alarm.alarmRepeat(8, 15, 0, turnOff);

  // Evening (5pm)
  Alarm.alarmRepeat(17, 0, 0, turnOn);
  Alarm.alarmRepeat(17, 15, 0, turnOff);
}

void loop() {
  DateTime now = rtc.now();
  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());

  Alarm.delay(100);  // check & trigger alarms
}

void turnOn() {
  digitalWrite(relay_pin, HIGH);
}

void turnOff() {
  digitalWrite(relay_pin, LOW);
}
