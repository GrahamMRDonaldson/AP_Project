#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */

// SAMPLE VARS
float RegFreq[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25 };      // regular values
float PosFreq[8] = {274.7115, 308.343, 346.1115, 366.6915, 411.6, 462, 518.574, 549.4125}; // 5%
float NegFreq[8] = {248.5485, 278.977, 313.1485, 331.7685, 372.4, 418, 469.186, 497.0875}; // -5%

// CHANGE THESE VARS
const uint16_t samples = 32; // 16, 32, 64, 128
const double sampling = 1100;        // sampling Frequency rate (at least double the max freq we should test (aka 550*2) = 1100

// DONT CHANGE THESE VARS
double RealSig[samples];
double ImagSig[samples];
uint8_t exponent;
int sleep_time   = 100; // sleep time between each signal point 10Hz sampling @ 100,

// PINS
int PIN_IN = A1;
int LED_1 = 2; // LED Output
int LED_2 = 3; // LED Output
int LED_3 = 4; // LED Output
int LED_4 = 5; // LED Output
int LED_5 = 6; // LED Output
int LED_6 = 7; // LED Output
int LED_7 = 8; // LED Output
int LED_8 = 9; // LED Output

// updates the output of the LED's given a frequency
bool Between(int note, double frequency){
  if(note < 0)
  {
     return false;
  }
  if(note > 7)
  {
    return false;
  }
  if(frequency < PosFreq[note] && frequency > NegFreq[note])
  {
    return true;
  }
    
  return false;
}

// returns note of closest frequency (1-8)
int ClosestTo(double frequency) {
  double BestDelta = 10000;
  int BestNote = -1;
  for(int i = 0; i < 8; i++)
  {
    double TargFreq = RegFreq[i];
    double delta = abs(TargFreq - frequency);
    if(delta < BestDelta)
    {
      BestDelta = delta;
      BestNote = i;
    }
  }
  return BestNote + 1;
}

void UpdateLED(double frequency){
  static int PrevNote = 0;
  int Note = 0;

  if(Between(0, frequency))
    Note = ClosestTo(frequency);
  else if(Between(1, frequency))
    Note = ClosestTo(frequency);
  else if(Between(2, frequency))
    Note = ClosestTo(frequency);
  else if(Between(3, frequency))
    Note = ClosestTo(frequency);
  else if(Between(4, frequency))
    Note = ClosestTo(frequency);
  else if(Between(5, frequency))
    Note = ClosestTo(frequency);
  else if(Between(6, frequency))
    Note = ClosestTo(frequency);
  else if(Between(7, frequency))
    Note = ClosestTo(frequency);

  Serial.print("NOTE:\t");
  Serial.print(frequency);
  Serial.print("\t");
  switch (Note) {
    case 1:
      Serial.println("C-LOW");
      break;
    case 2:
      Serial.println("D");
      break;
    case 3:
      Serial.println("E");
      break;
    case 4:
      Serial.println("F");
      break;
    case 5:
      Serial.println("G");
      break;
    case 6:
      Serial.println("A");
      break;
    case 7:
      Serial.println("B");
      break;
    case 8:
      Serial.println("C-HIGH");
      break;
    default:
      Serial.println("InValid");
      break;
  }
   

  // Make it so LED's only change on state change
  if(Note == PrevNote)
    return;

  PrevNote = Note;
  switch (Note) {
  case 1:
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    break;
  case 2:
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    break;
  case 3:
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    break;
  case 4:
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    break;
  case 5:
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    break;
  case 6:
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    break;
  case 7:
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_8, LOW);
    break;
  case 8:
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    break;
  default:
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    break;
  }
}

// SETUP
void setup() {
  Serial.begin(9600);           //  setup serial
  sleep_time = 1 / (sampling / 1000);
  Serial.println("Ready");
  exponent = FFT.Exponent(samples);
}

// GET SOME VALUES FROM SIGNAL (0-19)
void UpdateSIGNAL() {
  for (int i = 0; i < 20; i++) {
    RealSig[i] = analogRead(PIN_IN); // get the value in
    ImagSig[i] = 0;
    Serial.println(RealSig[i]); // print it
    delay(sleep_time); // sleep the proper amount
  }
}

// Simulate Signal
void SimSignal(double frequency) {
  double cycles = (((samples-1) * frequency) / sampling);
  for (uint16_t i = 0; i < samples; i++)
  {
    RealSig[i] = int8_t((4 * (sin((i * (twoPi * cycles)) / samples))) / 2.0);
    ImagSig[i] = 0; //Reset the imaginary values vector for each new frequency
  }
}

void loop() {
  double LowFreq = 200;
  double HighFreq = 600;
  for(double i = LowFreq; i < HighFreq; i++)
  {
    //UpdateSIGNAL();
    SimSignal(i); // A

    FFT.Windowing(RealSig, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
    FFT.Compute(RealSig, ImagSig, samples, exponent, FFT_FORWARD); /* Compute FFT */
    FFT.ComplexToMagnitude(RealSig, ImagSig, samples); /* Compute magnitudes */
    double x = FFT.MajorPeak(RealSig, samples, sampling);

    UpdateLED(x);
  }
  while(1);
}
