void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  testtouchsensor();
  led();
}

void loop() {
  // put your main code here, to run repeatedly:
  linefollowing();
 //testSensors();
}

#define LED 13

void led(){
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);
}
