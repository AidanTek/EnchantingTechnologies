/*
Synthesizer example using the Teensy to produce sound. Two chords are made up by 6 oscillators split into two groups of three.
Each group sums into a low pass filter, over time the low pass filters are crossfaded with each other. 

I am using the Teensy 3.2 and Prop Shield, but this example should work on its own with the DAC output on the Teensy connected
directly to an amplifier. I designed the DSP using the Teensy Audio System Design Tool: https://www.pjrc.com/teensy/gui/

Developed as part of the Enchanting Technologies Fab-Cre8 Project
Sketch by Aidan Taylor 2018
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformModulated wave6; //xy=138,470
AudioSynthWaveformModulated wave3;   //xy=139,356
AudioSynthWaveformModulated wave4; //xy=139,402
AudioSynthWaveformModulated wave1;   //xy=140,288
AudioSynthWaveformModulated wave5; //xy=140,436
AudioSynthWaveformModulated wave2;   //xy=141,322
AudioMixer4              mix2; //xy=300,442
AudioMixer4              mix1;         //xy=301,328
AudioFilterStateVariable filter2; //xy=439,448
AudioFilterStateVariable filter1;        //xy=440,334
AudioAmplifier           amp2; //xy=587,436
AudioAmplifier           amp1;           //xy=588,322
AudioMixer4              mix3; //xy=737,392
AudioOutputAnalog        dac1;           //xy=873,392
AudioConnection          patchCord1(wave6, 0, mix2, 2);
AudioConnection          patchCord2(wave3, 0, mix1, 2);
AudioConnection          patchCord3(wave4, 0, mix2, 0);
AudioConnection          patchCord4(wave1, 0, mix1, 0);
AudioConnection          patchCord5(wave5, 0, mix2, 1);
AudioConnection          patchCord6(wave2, 0, mix1, 1);
AudioConnection          patchCord7(mix2, 0, filter2, 0);
AudioConnection          patchCord8(mix1, 0, filter1, 0);
AudioConnection          patchCord9(filter2, 0, amp2, 0);
AudioConnection          patchCord10(filter1, 0, amp1, 0);
AudioConnection          patchCord11(amp2, 0, mix3, 1);
AudioConnection          patchCord12(amp1, 0, mix3, 0);
AudioConnection          patchCord13(mix3, dac1);
// GUItool: end automatically generated code

byte ampEnable = 5;

void setup() {
  //Activate Serial Port
  Serial.begin(115200);
  while(!Serial);

  // Allow some memory for audio connections
  AudioMemory(8);
  delay(2000);

  // Enable the amplifier on the prop shield:
  pinMode(ampEnable, OUTPUT);
  digitalWrite(5, HIGH); // turn on the amplifier
  delay(10);             // allow time to wake up
  
  // Amin chord
  wave1.begin(0.6, 220.0, WAVEFORM_SAWTOOTH); // A3
  wave2.begin(0.6, 261.626, WAVEFORM_SAWTOOTH); // C4
  wave3.begin(0.6, 164.814, WAVEFORM_SAWTOOTH); // E3 - lower E

  // Amin chord
  wave4.begin(0.6, 294.665, WAVEFORM_SAWTOOTH); // D4
  wave5.begin(0.6, 350.228, WAVEFORM_SAWTOOTH); // G4
  wave6.begin(0.6, 441.0, WAVEFORM_SAWTOOTH); // A4

  mix1.gain(0, 0.8);
  mix1.gain(1, 0.8);
  mix1.gain(2, 0.8);

  mix2.gain(0, 0.8);
  mix2.gain(1, 0.8);
  mix2.gain(2, 0.8);

  filter1.frequency(0);
  filter1.resonance(0.8);

  filter2.frequency(0);
  filter2.resonance(0.8);

  amp1.gain(0.1); // This can get loud!!
  amp2.gain(0.1); // This can get loud!!
  
}

void loop() {
  Serial.print("Let the drone begin...");
  for(int i = 120; i < 10000; i++) {
    filter1.frequency(i);
    filter2.frequency(10000-i);
    delay(1);
  }
  for(int i = 10000; i > 120; i--) {
    filter1.frequency(i);
    filter2.frequency(10000-i);
    delay(1);
  }
}
