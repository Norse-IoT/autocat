/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ds1307-rtc-module
 */

#include <RTClib.h>
// #include <TimeAlarms.h>  // needs TimeAlarms@1.5 by Michael Margolis
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
  // set rtc to compile time.
  // Note that this line should be used once, then removed, lest the RTC chip be overwritten if the Arduino loses power.
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  testMotor();
}

void printTime() {
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
}

void loop() {
  DateTime now = rtc.now();

  // Based on my measurements, 10 minutes on = 1 cup of food.
  // This should use 3 cups of food per day.

  if (now.hour() == 8 && now.minute() >= 0 && now.minute() < 10) {
    // Morning (8am) - 2 cups
    turnOn();
  } else if (now.hour() == 17 && now.minute() >= 0 && now.minute() < 10) {
    // Evening (5pm) - 1 cup
    turnOn();
  } else {
    turnOff();
  }

  printTime();
}

void turnOn() {
  Serial.println("ON!");
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(relay_pin, HIGH);
}

void turnOff() {
  Serial.println("OFF!");
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(relay_pin, LOW);
}

void testMotor() {
  turnOn();
  delay(10 * 1000);  // 10 seconds
  turnOff();
}
