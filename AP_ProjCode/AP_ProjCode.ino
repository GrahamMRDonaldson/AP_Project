#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */

// CHANGE THESE VARS
const uint16_t samples = 32; // 16, 32, 64, 128
const double sampling = 1100;        // sampling Frequency rate (at least double the max freq we should test (aka 550*2) = 1100

// DONT CHANGE THESE VARS
double RealSig[samples];
double ImagSig[samples];
uint8_t exponent;

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

// PINS
int PIN_IN = A1;
int sleep_time   = 100; // sleep time between each signal point 10Hz sampling @ 100, 

void setup() {
  Serial.begin(9600);           //  setup serial
  sleep_time = 1 / (sampling / 1000);
  Serial.println("Ready");
  exponent = FFT.Exponent(samples);
}

// GET SOME VALUES FROM SIGNAL (0-19)
void UpdateSIGNAL()
{
  for (int i = 0; i < 20; i++) {
    RealSig[i] = analogRead(PIN_IN); // get the value in
    ImagSig[i] = 0;
    Serial.println(RealSig[i]); // print it
    delay(sleep_time); // sleep the proper amount
  }
}

void SimSignal(double frequency)
{
  double cycles = (((samples-1) * frequency) / sampling);
  for (uint16_t i = 0; i < samples; i++)
  {
    RealSig[i] = int8_t((4 * (sin((i * (twoPi * cycles)) / samples))) / 2.0);
    ImagSig[i] = 0; //Reset the imaginary values vector for each new frequency
  }
}

void loop() {
  // Get Signal
  //UpdateSIGNAL();
  while(true)
  { 
    SimSignal(550.0); // A
    
    FFT.Windowing(RealSig, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
    FFT.Compute(RealSig, ImagSig, samples, exponent, FFT_FORWARD); /* Compute FFT */
    FFT.ComplexToMagnitude(RealSig, ImagSig, samples); /* Compute magnitudes */
    double x = FFT.MajorPeak(RealSig, samples, sampling);
    Serial.println(x);
  }
}
