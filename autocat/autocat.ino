#include <Stepper.h>

const int steps_per_rev = 2048;

#define IN1 26
#define IN2 25
#define IN3 33
#define IN4 32

Stepper motor(steps_per_rev, IN1, IN3, IN2, IN4);

void setup() {
  motor.setSpeed(10);
  Serial.begin(115200);
}

void loop() {
  Serial.println("Rotating Clockwise...");
  motor.step(steps_per_rev);
  delay(60 * 1000);

}