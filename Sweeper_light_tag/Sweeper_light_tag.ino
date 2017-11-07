
// Detects hand and switches sound
// Part 2: Light Tag

#define PHOTOSENSOR 19
#define brightness 989
#define speaker 4


int frequency[18] = {294, 294, 392, 587, 523, 494, 440, 784,
                     587, 523, 494, 440, 784, 587, 523, 494, 523, 440
                    };

int duration[18] = {220, 220, 970, 470, 135, 135, 135, 970,
                    470, 135, 135, 135, 970, 470, 135, 135, 135, 1470
                   };

void setup() {
  pinMode(PHOTOSENSOR, INPUT);
}

void loop() {

  while (analogRead(PHOTOSENSOR - 14) > brightness) // if hand present
  {
    for (int i = 0; i < 18; i ++)
    { // for loop from i 0 to 18 frequency
      tone (speaker, frequency[i], duration[i]); // creates a tone based on frequency and duration
      delay(duration[i]); // causes delay for duration of frequency, so not overlap
      delay(30); // causes time dealy of 30ms for proper sounds

      if (analogRead(PHOTOSENSOR - 14) < brightness) // if hand removed
      {
        break; / stop
      }
    }
    tone(speaker, 405, 1500); // play other note
    delay(1500); // delay so you can hear sound
    noTone(speaker); // turn off speaker
    }
}
