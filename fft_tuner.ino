#include "arduinoFFT.h"

const uint16_t samples = 1024; 
const double samplingFrequency = 5000;

double vReal[samples];
double vImag[samples];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency);
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

String semitones[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};


void setup() {
  
  Serial.begin(115200);
  analogReadResolution(12);
  

}

void loop() {
  unsigned long period = 1000000UL / samplingFrequency;
  unsigned long next = micros();
  for (int i = 0; i < samples; i++)
  {
    while(micros() < next){}
    vReal[i] = analogRead(34);
    vImag[i] = 0.0; 
    next += period;
  }
  FFT.dcRemoval();
  FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);
  FFT.compute(FFTDirection::Forward);
  FFT.complexToMagnitude();
  if(FFT.majorPeak() > 65.41) Serial.println(freqToNote(FFT.majorPeak()));
  
}

String freqToNote(double frequency){
  double stepsExact =  12*(log(frequency/16.35)/log(2));
  int stepsRound = (int) round(12*(log(frequency/16.35)/log(2)));
  int cents = (int) (100* (stepsExact - (double)stepsRound)) ; 
  int octave = 0; 
  if(abs(stepsRound) >= 12){
    for(int i = stepsRound; i >= 12; i-=12){
      octave += 1;
    }
    stepsRound = stepsRound % 12; 
  }
  if(stepsRound <0){
    stepsRound = 12+ stepsRound; 
  }
  if(cents >= 0) return semitones[stepsRound] + octave + " cents: +" + cents;
  return semitones[stepsRound] + octave + " cents: " + cents;
  
}
