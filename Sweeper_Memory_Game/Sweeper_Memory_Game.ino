// Memory game for guessing LED flashed

# define LEDRED 13
# define LEDGREEN 5
# define header 15

int robotArray[8] = {}; // create array for robot
int humanArray[8] = {}; // create array for human input

void setup() {
  Serial.begin(9600); // startup code for LED lightts
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDGREEN, OUTPUT);
  randomSeed(analogRead(header)); // randomize function

}

void loop() {
  Serial.println("Randomly flashing lights now!");
  generateLEDFlashes(); // setup of functions
  Serial.println("Enter your guess human.");
  getUserResponse();
  correlate();
  promptUser();
}

void generateLEDFlashes()
{
  for (int i = 0; i < 8; i ++) { // array for loop
    robotArray[i] = random(0, 2); // have random values of 0 or 1 in array
  }
  for (int i = 0; i < 8; i ++) { // array for loop
    if (robotArray[i] == 0) {
      digitalWrite(LEDRED, HIGH); // make LED high
      delay(600); // delay to observe the blinking
      digitalWrite(LEDRED, LOW);
      delay(600);

    }
    else if (robotArray[i] == 1) {
      digitalWrite(LEDGREEN, HIGH); // repeat same idea as above for green light
      delay(600);
      digitalWrite(LEDGREEN, LOW);
      delay(600);

    }
  }
}

void getUserResponse()
{
  for (int i = 0; i < 8; i ++)
  {
    if (Serial.available())
    {
      humanArray[i] = Serial.read() - 48; // convert from ascii
      Serial.println(humanArray[i]); // print what you put in
    }
    else
    {
      i = i - 1; // need to revert one backwards if it runs when no input
    }
  }
}

void correlate()
{
  int x = 0;
  int i = 0;
  while (i < 8)
  {
    if (humanArray[i] == robotArray[i]) // checks if the values correspond
    { // if the values correspond
      x = x + 1; // add one point
    }
    else {
      x = x - 1; // subtract one point for wrong answer
    }
    i++; // repeat
  }
  Serial.println("Human, your score is:");
  Serial.println(x); // prints score
}

void promptUser()
{
  Serial.println("Hit a key to play again!"); // tell user to press key
  unsigned char pressed;
  while (Serial.available() == 0) { // if no input, do not continue loop
  }
  while (Serial.available() == 0) { // if input
    pressed = Serial.read() - 48; // compute the loop, move to next function
  }

}

