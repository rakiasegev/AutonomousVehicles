#include <Servo.h>
// pins
#define SERVOPIN 10

// global variable for the servo information
Servo servo;

void testServo()
{
  initServo();
  servo.write(0);delay(2000);
  servo.write(45);delay(2000);
  servo.write(90);delay(2000);
  servo.write(135);delay(2000);
  servo.write(180);delay(2000);

}

void initServo()
{
  pinMode(SERVOPIN, OUTPUT);
  servo.attach(SERVOPIN);
}



