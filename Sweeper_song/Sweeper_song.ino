// program causes arduion robot to play Star Wars theme song
# define pin 4

int frequency[18] = {294, 294, 392, 587, 523, 494, 440, 784,
                     587, 523, 494, 440, 784, 587, 523, 494, 523, 440
                    };

int duration[18] = {220, 220, 970, 470, 135, 135, 135, 970,
                    470, 135, 135, 135, 970, 470, 135, 135, 135, 1470
                   };

void setup() {
  pinMode(pin, OUTPUT); // setting up output for pin
}

void loop() {
  for (int i = 0; i < 18; i ++)
  { // for loop from i 0 to 18 frequency
    tone (pin, frequency[i], duration[i]); // creates a tone based on frequency and duration
    delay(duration[i]); // causes delay for duration of frequency, so not overlap
    delay(30); // causes time dealy of 30ms for proper sounds
  }

}
