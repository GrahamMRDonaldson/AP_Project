// CHANGE THESE VARS
float freq = 1100;        // sampling Frequency rate (at least double the max freq we should test (aka 550*2)

// DONT CHANGE THESE VARS
int SIGNAL[20];       // we have a signal with 20 capture points
int LED[8];           // 8 LEDs
int sleep_time = 100; // sleep time between each signal point 10Hz sampling @ 100, 
int E = 2.7182818;    // little e val
float RegFreq[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25 };      // regular values
float PosFreq[8] = {274.7115, 308.343, 346.1115, 366.6915, 411.6, 462, 518.574, 549.4125}; // 5%
float NegFreq[8] = {248.5485, 278.977, 313.1485, 331.7685, 372.4, 418, 469.186, 497.0875}; // -5%

// PINS
int PIN_IN = A1;

// FFT for an individual freqency
float FTT(int freq)
{
  float final = 0;
  for (int i = 0; i < 20; i++)
    final += SIGNAL[i] * pow(E, freq*i);
  return final;
}

// Get the values, and indicate what LEDS are lit up
void UpdateFFT()
{
  // GET SOME VALUES FROM SIGNAL (0-19
  for (int i = 0; i < 20; i++) {
    SIGNAL[i] = analogRead(PIN_IN); // get the value in
    Serial.println(SIGNAL[i]); // print it
    delay(sleep_time); // sleep the proper amount
  }

  // TODO - do summation instead of avg if it working well
  // Prints out FT response for 8 selected frequencies
  for(int i = 0; i < 8; i++)
  {
    float left = FTT(NegFreq[i]);   // gets left most (lower freq)
    float right = FTT(PosFreq[i]);  // gets right most (higher freq)
    float mid = FTT(RegFreq[i]);    // gets mid (exact freq)
    float avg = (mid + left + right) / 3; //gets thea avg of those above^
    Serial.print(avg); // prints average
    if(i != 8)
      Serial.print(" | ");
  }
  Serial.println("");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           //  setup serial
  // convert to sec, than inverse (sampling freq --> time sleep)
  sleep_time = 1 / (freq / 1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  UpdateFFT();
  while(true)
    delay(100000);

}
