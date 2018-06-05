#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformModulated waveformMod3;   //xy=216,192
AudioSynthWaveformModulated waveformMod4;   //xy=217,235
AudioSynthWaveformModulated waveformMod1;   //xy=218,93
AudioSynthWaveformModulated waveformMod2;   //xy=218,142
AudioSynthWaveformModulated waveformMod5;   //xy=219,279
AudioSynthWaveformModulated waveformMod6;   //xy=219,324
AudioSynthWaveformModulated waveformMod7;   //xy=220,370
AudioMixer4              mixer2;         //xy=428,243
AudioMixer4              mixer1;         //xy=430,179
AudioMixer4              mixer3;         //xy=565,221
AudioFilterStateVariable filter1;        //xy=718,278
AudioOutputAnalog        dac1;           //xy=846,265
AudioConnection          patchCord1(waveformMod3, 0, mixer1, 2);
AudioConnection          patchCord2(waveformMod4, 0, mixer1, 3);
AudioConnection          patchCord3(waveformMod1, 0, mixer1, 0);
AudioConnection          patchCord4(waveformMod2, 0, mixer1, 1);
AudioConnection          patchCord5(waveformMod5, 0, mixer2, 0);
AudioConnection          patchCord6(waveformMod6, 0, mixer2, 1);
AudioConnection          patchCord7(waveformMod7, 0, mixer2, 2);
AudioConnection          patchCord8(mixer2, 0, mixer3, 1);
AudioConnection          patchCord9(mixer1, 0, mixer3, 0);
AudioConnection          patchCord10(mixer3, 0, filter1, 0);
AudioConnection          patchCord11(filter1, 0, dac1, 0);
// GUItool: end automatically generated code

const uint8_t ampEnable = 5;
const uint8_t touchPin[7] = {0,1,15,16,17,22,23};
const uint16_t touchSens = 500;

const float ampRate = 0.0001;

uint16_t touchThresh[7];

void setup() {
  Serial.begin(115200);
  // If you want to use the native serial port, you should uncomment the below:
  while(!Serial);

  AudioMemory(8);
  delay(2000);
  
  // Activate the amplifier:
  pinMode(ampEnable, OUTPUT);
  digitalWrite(ampEnable, HIGH);
  delay(10);

  // Calibrate touch sensitivity:
  uint16_t touchVal[7];
  for(uint8_t n = 0; n < 7; n++) {
    touchThresh[n] = (touchRead(touchPin[n])+touchSens);
  }

  waveformMod1.begin(0.8, 130.8, WAVEFORM_SAWTOOTH);
  waveformMod2.begin(0.8, 146.8, WAVEFORM_SAWTOOTH);
  waveformMod3.begin(0.8, 164.8, WAVEFORM_SAWTOOTH);
  waveformMod4.begin(0.8, 174.6, WAVEFORM_SAWTOOTH);
  waveformMod5.begin(0.8, 196.0, WAVEFORM_SAWTOOTH);
  waveformMod6.begin(0.8, 220.0, WAVEFORM_SAWTOOTH);
  waveformMod7.begin(0.8, 246.9, WAVEFORM_SAWTOOTH);

  mixer1.gain(0, 0.);
  mixer1.gain(1, 0.);
  mixer1.gain(2, 0.);
  mixer1.gain(3, 0.);
  mixer2.gain(0, 0.);
  mixer2.gain(1, 0.);
  mixer2.gain(2, 0.);
  mixer2.gain(3, 0.);

  mixer3.gain(0, 0.8);
  mixer3.gain(1, 0.8);
  filter1.frequency(2000);
  filter1.resonance(0.5);
}

void loop() {
  uint16_t touchVal[7];
  bool voiceOn[7];
  uint32_t mainTimer;
  uint32_t testTimer;

  float v1Amp = 0.;
  float v2Amp = 0.;
  float v3Amp = 0.;
  float v4Amp = 0.;
  float v5Amp = 0.;
  float v6Amp = 0.;
  float v7Amp = 0.;

  float freqTable[7] = {130.8, 146.8, 164.8, 174.6, 196.0, 220.0, 246.9};

  // Generate some poor tuning for analogue simulation!
  for(uint8_t n = 0; n < 7; n++) {
    float randNum = (random(100, 105))*0.01;
    Serial.println(randNum);
    freqTable[n] = freqTable[n]*randNum;
    Serial.println(freqTable[n]);
  }

  waveformMod1.frequency(freqTable[0]);
  waveformMod2.frequency(freqTable[1]);
  waveformMod3.frequency(freqTable[2]);
  waveformMod4.frequency(freqTable[3]);
  waveformMod5.frequency(freqTable[4]);
  waveformMod6.frequency(freqTable[5]);
  waveformMod7.frequency(freqTable[6]);

  float filterLFO = 3000.0;
  bool LFODir = 0;
  
  while(true) {
    // update touch readings
    for(uint8_t n = 0; n < 7; n++) {
      touchVal[n] = touchRead(touchPin[n]);
      if(touchVal[n] > touchThresh[n]) {
        voiceOn[n] = 1;
      }
      else voiceOn[n] = 0;
  
//      if(n != 6) {
//        Serial.print(voiceOn[n]);
//        Serial.print(" ,");
//      }
//      else Serial.println(voiceOn[n]);
    }
  
    mainTimer = millis();
    if(mainTimer - testTimer > 1) {
      testTimer = millis();
   
      if(voiceOn[0]) {
        if(v1Amp < 0.7) {
          v1Amp = v1Amp + ampRate;
          mixer1.gain(0, v1Amp);
        }
      }
      else {
        if(v1Amp > 0.0) {
          v1Amp = v1Amp - ampRate;
          mixer1.gain(0, v1Amp);
        }
      }

      if(voiceOn[1]) {
        if(v2Amp < 0.7) {
          v2Amp = v2Amp + ampRate;
          mixer1.gain(1, v2Amp);
        }
      }
      else {
        if(v2Amp > 0.0) {
          v2Amp = v2Amp - ampRate;
          mixer1.gain(1, v2Amp);
        }
      }

      if(voiceOn[2]) {
        if(v3Amp < 0.7) {
          v3Amp = v3Amp + ampRate;
          mixer1.gain(2, v3Amp);
        }
      }
      else {
        if(v3Amp > 0.0) {
          v3Amp = v3Amp - ampRate;
          mixer1.gain(2, v3Amp);
        }
      }

      if(voiceOn[3]) {
        if(v4Amp < 0.7) {
          v4Amp = v4Amp + ampRate;
          mixer1.gain(3, v4Amp);
        }
      }
      else {
        if(v4Amp > 0.0) {
          v4Amp = v4Amp - ampRate;
          mixer1.gain(3, v4Amp);
        }
      }

      if(voiceOn[4]) {
        if(v5Amp < 0.7) {
          v5Amp = v5Amp + ampRate;
          mixer2.gain(0, v5Amp);
        }
      }
      else {
        if(v5Amp > 0.0) {
          v5Amp = v5Amp - ampRate;
          mixer2.gain(0, v5Amp);
        }
      }

      if(voiceOn[5]) {
        if(v6Amp < 0.7) {
          v6Amp = v6Amp + ampRate;
          mixer2.gain(1, v6Amp);
        }
      }
      else {
        if(v6Amp > 0.0) {
          v6Amp = v6Amp - ampRate;
          mixer2.gain(1, v6Amp);
        }
      }

      if(voiceOn[6]) {
        if(v7Amp < 0.7) {
          v7Amp = v7Amp + ampRate;
          mixer2.gain(2, v7Amp);
        }
      }
      else {
        if(v7Amp > 0.00) {
          v7Amp = v7Amp - ampRate;
          mixer2.gain(2, v7Amp);
        }
      }

      // Basic LFO for filter:
      if(filterLFO = 200.0 || filterLFO = 5000.0) {
        LFODir = !LFODir;
      }

      
      
    }
  } 
}
