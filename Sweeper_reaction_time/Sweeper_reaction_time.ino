// Distance sensor detecting human hand

// Part 1: Reaction Timer

#define handdistance 201
#define speaker 4
#define DISTSENSOR 14

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DISTSENSOR, INPUT); // define pinmode for distance sensor
  int dist = analogRead(DISTSENSOR - 14); // reads distance

}

void loop() {
  // 
  // Serial.println(analogRead(DISTSENSOR - 14)); 
  // delay(1000);
  while (analogRead(DISTSENSOR - 14) < handdistance) // hand in front
  {
  }
  int wait = random(300, 3000);
  tone(speaker, 257, wait); // play a note 
  delay(wait); // wait for duration of the note
  noTone(speaker); // turn speaker off
  tone(speaker, 504, 2000); // play a different note
  unsigned long currenttime = millis(); / measure current time // check time
  while (analogRead(DISTSENSOR - 14) > handdistance) // no hand in front
  {
  }
  noTone(speaker); // stop speaker
  unsigned long finaltime = millis();  // measure new time
  unsigned long timedifference = finaltime - currenttime; // find chnage in time
  Serial.println(timedifference); // print time to move hand
}


