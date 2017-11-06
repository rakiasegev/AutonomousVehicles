
#define REFLSENSOR 18
#define B 960
#define W 880
#define G1 930
#define G2 950

void linefollowing() {
  int reflect = analogRead(REFLSENSOR - 14);
  Serial.println(reflect);

  if (reflect > B) //forward when black
  {
    forward();
  }
  else if (reflect < W) // turn right when white
  {
    turnR();
  }
  else if (reflect > 910 && reflect < 950)
  {
    turnL();
  }

}

