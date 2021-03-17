// CHANGE THESE VARS
#define samples 512 // 16, 32, 64, 128
const double sampling = 10500;        // sampling Frequency rate (at least double the max freq we should test (aka 550*20) = 10500
unsigned int sampling_period_us;
int Signal[samples];
int LED_BYTE;
unsigned long microseconds;

#define BIT_1 1
#define BIT_2 2
#define BIT_3 4
#define BIT_4 8
#define BIT_5 16
#define BIT_6 32
#define BIT_7 64
#define BIT_8 128

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

#define FASTADC 1

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif



void setup() {
  // set prescale to 8
    cbi(ADCSRA,ADPS2) ;
    sbi(ADCSRA,ADPS1) ;
    sbi(ADCSRA,ADPS0) ;

  Serial.begin(115200);           //  setup serial
  sampling_period_us = round(1000000*(1.0/sampling));
  //Serial.println(sampling_period_us);
}


void UpdateSignal() {
  for (int i = 0; i < samples; i++) {
    microseconds = micros();    
    Signal[i] = analogRead(PIN_IN); // get the value in
    //Serial.println(Signal[i]);
    while(micros() < (microseconds + sampling_period_us)){}
  }
}

void SendSignal()
{
  for (int i = 0; i < samples; i++) {
     Serial.println(String(Signal[i]));
  }
}

void GetData()
{
  //delay(1000); //wait a second, beore receiving data, and writing to LED's
  if (Serial.available() > 0) {
    // read the incoming byte:
    LED_BYTE = Serial.read();
  }

  if(LED_BYTE & BIT_1)
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
  } else if(LED_BYTE & BIT_2)
  {
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
  } else if(LED_BYTE & BIT_3)
  {
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
  }else if(LED_BYTE & BIT_4)
  {
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
  } else if(LED_BYTE & BIT_5)
  {
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
  } else if(LED_BYTE & BIT_6)
  {
    digitalWrite(LED_6, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
  } else if(LED_BYTE & BIT_7)
  {
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_8, LOW);
  } else if(LED_BYTE & BIT_8) {
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
  } else {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
  }
}

void loop() {
  UpdateSignal();
  SendSignal();
  GetData();
  

}
