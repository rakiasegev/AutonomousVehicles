#define DISTSENSOR 14
#define REFLSENSOR 18
#define PHOTOSENSOR 19
#define TOUCHSENSOR 2

void testSensors() {
  pinMode(DISTSENSOR, INPUT);
  int dist = analogRead(DISTSENSOR - 14);
  pinMode(REFLSENSOR, INPUT);
  int dist1 = analogRead(REFLSENSOR - 14);
  pinMode(PHOTOSENSOR, INPUT);
  int dist2 = analogRead(PHOTOSENSOR - 14);
  pinMode(TOUCHSENSOR, INPUT);
  int dist3 = digitalRead(TOUCHSENSOR);

  Serial.print("DISTSENSOR,");
  Serial.print(dist  );
  Serial.print("   REFLSENSOR,");
  Serial.print(dist1  );
  Serial.print("  PHOTOSENSOR,");
  Serial.println(dist2 );
  delay(400);
}

void testPhototransistor() {
  if (analogRead(PHOTOSENSOR - 14) > 260)
  {
    turnL();
  }
  else
  {
    forward();
  }
}

void testReflsensor() {
  if (analogRead(REFLSENSOR - 14) > 350)
  {
    void halt();
  }
  else
  {
    forward();
  }

}
bool testtouchsensor()
{
  while (digitalRead(TOUCHSENSOR) != HIGH) {
    Serial.println("hi");
    forward();
    }
    if (digitalRead(TOUCHSENSOR) == HIGH) {
      halt();
      delay(6000);
      backward();
      delay(500);
      halt();

  }
}

