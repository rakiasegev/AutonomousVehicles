# define LPLUS 9
# define LMINUS 8
# define RPLUS 7
# define RMINUS 12
# define LEN 6
# define REN 11


void initMotors()
{
  pinMode(LPLUS, OUTPUT);
  pinMode(LMINUS, OUTPUT);
  pinMode(RPLUS, OUTPUT);
  pinMode(RMINUS, OUTPUT);
}

void halt()
{
  digitalWrite(LPLUS, LOW);
  digitalWrite(LMINUS, LOW);
  digitalWrite(RPLUS, LOW);
  digitalWrite(RMINUS, LOW);
  digitalWrite(LEN, HIGH);
  digitalWrite(REN, LOW);
}

void forward()
{
  digitalWrite(LEN, HIGH);
  digitalWrite(LPLUS, LOW);
  digitalWrite(LMINUS, HIGH);

  digitalWrite(REN, HIGH);
  digitalWrite(RPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
}

void backward()
{
  digitalWrite(LPLUS, HIGH);
  digitalWrite(LMINUS, LOW);

  digitalWrite(RPLUS, HIGH);
  digitalWrite(RMINUS, LOW);
}

void turnL()
{
  digitalWrite(LEN, HIGH);
  digitalWrite(LPLUS, HIGH);
  digitalWrite(LMINUS, LOW);

  digitalWrite(REN, HIGH);
  digitalWrite(RPLUS, LOW);
  digitalWrite(RMINUS, HIGH);
}

void turnR()
{
  digitalWrite(LEN, HIGH);
  digitalWrite(LPLUS, LOW);
  digitalWrite(LMINUS, HIGH);

  digitalWrite(REN, HIGH);
  digitalWrite(RPLUS, HIGH);
  digitalWrite(RMINUS, LOW);
}
