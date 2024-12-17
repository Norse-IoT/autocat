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

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

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

  // Set alarms
  Alarm.alarmRepeat(22, 24, 0, turnOn);   // Daily at 14:30:00
  Alarm.alarmRepeat(22, 25, 0, turnOff);  // Daily at 15:00:00
}

void loop() {
  DateTime now = rtc.now();
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  Alarm.delay(100);  // check & trigger alarms
}

void turnOn() {
  digitalWrite(relay_pin, HIGH);
}

void turnOff() {
  digitalWrite(relay_pin, LOW);
}
