// Code takes input from phototransitor and creates a binary array that 
// is then compared to gold code for stations and then identifies the station

#define numRegisters 5
#define numGoldCodes 9
#define PHOTOSENSOR 19
#define samplenum 31
#define LenGC 31


boolean gcs[numGoldCodes][samplenum] = {{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
  {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
  {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
  {1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1},
  {0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1}
};


int rawsamples[samplenum] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// initialize raw samples to empty array
boolean binarysamples[samplenum] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// create empty binary array

void photosensors() { // precursor function used to generate lines in loop
  unsigned long previousMicros = 0; // set timer to 0
  const long interval = 250; // every 250 micros read input
  unsigned long currentMicros = micros(); // reset current time

  int i = 0;
  while (0); { // iterate through constantly updating the GC and reading
    if (currentMicros - previousMicros >= interval) { // if the difference is >= interval
      // save the last time you read input
      previousMicros = currentMicros;
      rawsamples[i] =  analogRead(PHOTOSENSOR - 14); // filling up array
      i++;
      if (i == samplenum) {
        i = 0; // to read once GC

      }
    }
  }
}


int raw_average() {
  int sum = 0; // set sum equal to 0
  for ( int i = 0; i < 31; i++ ) // loop through entire array of sample numbrs
  {
    sum += rawsamples[i]; // add up all the values
  }
  return sum/samplenum; // divide by the length to compute average
}

int to_binary(int average, int raw_value) {
  if (raw_value > average) { // if value is greater than average, set binary to 0
    return 0;
  }
  else {
    return 1; // if value is less than average, set binary to 1

  }
}

void setup() {
  Serial.begin(9600);


}

int max_val = 0; // max correlation
int best_match = -1; // guess of the station

int correlateGC(boolean GC1[LenGC], boolean GC2[LenGC]) // correlate gold codes

{
  int M = 0; // set max to zero
  for ( int b = 0; b < LenGC; b++) // create loop for offset correlation, at offset b

  {
    int c = offsetcorrelate(GC1, GC2, b);
    if (abs(c) > abs(M)) // check if c value is larger than max (use absolute value)
    {
      M = c;
    }
    //Serial.print(c);
    //Serial.print(" ");
  }
  //Serial.println();
  //Serial.print("MAX: ");
  //Serial.println(M);
  return M; 
}

void trackGC() { // detects which gold code it is using correlate function
  max_val = 0;
  best_match = -1; // resetting global variales
  for ( int i = 0; i < 9; i++ ) { // iterating through 9 gold code stations
    int temp = correlateGC(binarysamples, gcs[i]); // checking generated binary sample to gcs
    if (abs(temp) > abs(max_val)) { // finding max correation (31)
      max_val = temp;
      best_match = i;
    }

  }
  return;
}

long int currentMicros = 0; // defining time as global variable
long int previousMicros = 0;
const int interval = 250;
int photo_counter = 0;
int AVERAGE = 0;

void loop() {

  currentMicros = micros(); // reset current time
  if (currentMicros - previousMicros >= interval) { // if the difference is >= interval
    // save the last time you read input
    previousMicros = currentMicros;

    rawsamples[photo_counter] =  analogRead(PHOTOSENSOR - 14); // filling up array
    binarysamples[photo_counter] = to_binary(AVERAGE, rawsamples[photo_counter]); // filling in binary samples
    photo_counter++;
    if (photo_counter == samplenum) {
      photo_counter = 0; // to read constantly GC and compared
      trackGC();
      Serial.print("Correlation ");
      Serial.print(max_val); // prints out correlation value
      Serial.print(", Station ");
      Serial.println(best_match); // prints out the station
   
      AVERAGE = raw_average();
    }

  }


}


// Code from gold code generation whose functions are called in detection

boolean seed1[numRegisters] = {0, 0, 0, 0, 1};
boolean seeds[numGoldCodes][numRegisters] = {{0, 0, 0, 0, 1}, {0, 0, 0, 1, 0}, {0, 0, 0, 1, 1}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 1}, {0, 0, 1, 1, 0}, {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}};
boolean poly1[numRegisters] = {0, 1, 1, 1, 1};
boolean poly2[numRegisters] = {0, 0, 1, 0, 1};
boolean Q1[numRegisters] = {0, 0, 0, 0, 0};
boolean Q2[numRegisters] = {0, 0, 0, 0, 0};
boolean D1, D2;
#define LenGC 31
boolean G1[8][LenGC]; // creating array to store gold code

int offsetcorrelate(boolean GC1[LenGC], boolean GC2[LenGC], int offset)
// define offset function
{
  int counter = 0;
  for (int i = 0; i < (LenGC); i++) // compute value for similarity of GC
  {
    if (GC1[i] == GC2[(i+offset)% LenGC]) // module GC2 so it doesn't pass length of array
    {
      counter = 1 + counter;
    }
    else
    {
      counter = counter -1;
      }
  }
return counter;
}

#if 0
int correlateGC(boolean GC1[LenGC], boolean GC2[LenGC]) // correlate gold codes

{
  int M = 0; // set max to zero
  for ( int b = 0; b < LenGC; b++) // create loop for offset correlation, at offset b

  {
    int c = offsetcorrelate(GC1, GC2, b);
    if (abs(c) > abs(M)) // check if c value is larger than max (use absolute value)
    {
      M = c;
    }
    Serial.print(c);
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("MAX: ");
  Serial.println(M);
  return M;

}
#endif 

#if 0
void setup()
{

  // Setup the serial connection for 9600
  Serial.begin(9600);


  // loop 8 times to create the 8 gold codes
  for ( int i = 0; i < 8; i++ )
  {


    //Call getGC to create the 8 goldcodes
    // send GC, the two polynomials poly1 and poly2 that
    // determine the feedback registers, as well as the
    // 8 different seeds and the index for which GC you
    // are creating
    getGC(poly1, poly2, seeds, i);

  }
  for ( int gcIndex = 0; gcIndex < 8; gcIndex++) { // create a loop to select GC to compare
    for ( int a = gcIndex; a < 8; a++) { // loop to select 2nd GC to compare
      Serial.print(" Correlation GC "); // printing the desired GC
      Serial.print(gcIndex+1);
      Serial.print(",");
      Serial.print(a+1);
      Serial.println(":");
      correlateGC(G1[gcIndex], G1[a]);
    }
  }

}

void loop()
{

}
#endif
// This function will calculate 1 gold code using the two polynomials and seeds
// Of the 8 gold codes to generate, it will calculate number "gcIndex"

void getGC(boolean p1[numRegisters], boolean p2[numRegisters], boolean s[numGoldCodes][numRegisters], int gcIndex)
{
  // Determine size of gold code
  int gcSize = pow(2, numRegisters) - 1; // 2^numRegisters - 1;

  // Create an array to store the goldcode
  boolean gc[gcSize];

  // Initialize D1 and D2 to be 1 here
  D1 = true;
  D2 = true;

  // Initialize the values of all the register bits in Q1 and Q2
  // to be the appropriate seeds from variables seed1 and seeds
  for (int i = 0; i < numRegisters; i++)
  {
    Q1[i] = seed1[i];
    Q2[i] = seeds[gcIndex][i];
  }

  // Run through all steps of shifting
  // i.e. use a for loop on gcSize
  Serial.print("Gold Code ");
  Serial.print(gcIndex + 1);
  Serial.print(": ");

  for ( int i = 0; i < gcSize; i++ )
  {
    // Set the i^th bit in the gold code to be the XOR of last two bits of Q1 and Q2
    gc[i] = XOR(Q1[4], Q2[4]);

    // Step all registers for both polynomials by calling the stepRegisters() function
    stepRegisters();

    // Print the gc to the screen
    Serial.print(gc[i]);
    G1[gcIndex][i] = gc[i];

  }

  Serial.println("");
}

void stepRegisters()
{

  // Calculate the values of D1 based on the
  // XOR of the registers in Q1 and the polynomial poly1
  // defining which registers are fed back. Then do the same for D2
  // These should call the feedbackXOR() function.
  D1 = feedbackXOR(Q1, poly1);
  D2 = feedbackXOR(Q2, poly2);


  // Use a for loop to countdown through all the registers,
  // to set up the shifting
  for ( int i = 4; i > 0; i--  )
  {
    // Shift, by setting each value of Q1[i], Q2[i] to the value
    // of Q1[i-1], Q2[i-1] respectively.
    Q1[i] = Q1[i - 1];
    Q2[i] = Q2[i - 1];
  }

  // Set the first value in Q1 and Q2 to be D1 and D2 respectively
  Q1[0] = D1;
  Q2[0] = D2;

}


// Input two arrays of booleans and output the XOR of them
int feedbackXOR(boolean p[numRegisters], boolean r[numRegisters])
{
  int sum = 0;

  // Loop through all the registers, starting at index 0
  for (int i = 0; i < 5; i++ )
  {

    // Increase the sum if both r[i] and p[i] are true
    if (r[i] && p[i])
    {
      sum = sum + 1;
    }

  }

  // If the sum is odd, return true
  // else, return false

  if (sum % 2 == 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Input two booleans and return the XOR of them
boolean XOR(boolean a, boolean b)
{

  // Return false if both a and b are the same value,
  // otherwise return true.
  if (a == b)
  {
    return false;
  }
  else
  {
    return true;
  }
}

