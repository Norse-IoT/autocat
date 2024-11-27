#include <Stepper.h>

const int steps_per_rev = 2048;

const int IN1 = 26;
const int IN2 = 25;
const int IN3 = 33;
const int IN4 = 32;
const int MOTOR_POWER = 2;

Stepper motor(steps_per_rev, IN1, IN3, IN2, IN4);

void setup() {
  pinMode(MOTOR_POWER, OUTPUT);
  motor.setSpeed(10);
  Serial.begin(115200);
}

void loop() {
  dispenseFood();
  delay(30 * 1000);
}

void dispenseFood() {
  digitalWrite(MOTOR_POWER, HIGH);
  delay(1000);  // TESTING
  Serial.println("Rotating Clockwise...");
  motor.step(steps_per_rev);
  Serial.println("Done!");
  delay(1000);  // TESTING
  digitalWrite(MOTOR_POWER, LOW);
}