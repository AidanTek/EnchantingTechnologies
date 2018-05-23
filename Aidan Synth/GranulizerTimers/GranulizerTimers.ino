// Trying out the new granular effect from the Teensy Audio library

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=210,384
AudioPlaySerialflashRaw  playFlashRaw2;  //xy=216,435
AudioMixer4              mixer1;         //xy=385,348
AudioEffectGranular      granular1;      //xy=525,348
AudioMixer4              mixer2;         //xy=651,427
AudioOutputAnalog        dac1;           //xy=778,427
AudioConnection          patchCord1(playFlashRaw1, 0, mixer1, 0);
AudioConnection          patchCord2(playFlashRaw1, 0, mixer2, 0);
AudioConnection          patchCord3(playFlashRaw2, 0, mixer1, 1);
AudioConnection          patchCord4(playFlashRaw2, 0, mixer2, 1);
AudioConnection          patchCord5(mixer1, granular1);
AudioConnection          patchCord6(granular1, 0, mixer2, 2);
AudioConnection          patchCord7(mixer2, dac1);
// GUItool: end automatically generated code


uint8_t ampEnable = 5; // This pin enables the amplifier when HIGH
uint8_t flashSelect = 6; // This pin is the flash chip select

#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];

long mainTimer = 0;
long granTest = 0;
int granInt = 8000;
long sample2Test = 0;
int sample2Int = 40000;

void setup() {
  Serial.begin(115200);
  
  // Audio connections require memory to work:
  AudioMemory(8);
  delay(2000);
  
  // Start SerialFlash
  if (!SerialFlash.begin(flashSelect)) {
    while (1) {
      Serial.println ("Cannot access SPI Flash chip");
      delay (1000);
    }
  }
  
  // Enable the amplifier on the prop shield:
  pinMode(ampEnable, OUTPUT);
  digitalWrite(5, HIGH); // turn on the amplifier
  delay(10);             // allow time to wake up

  // Preset the effect mixers (100% dry):
  mixer1.gain(0, 0.8); // Sample 1 FX in
  mixer1.gain(1, 0.8); // Sample 2 FX in

  mixer2.gain(0, 0.4); // Sample 1 direct
  mixer2.gain(1, 0.); // Sample 2 direct
  mixer2.gain(2, 0.4); // This is the effect return

  // The granular effect requires memory to operate:
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);

}

// A custom function to play first audio file:
void playRaw1(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);

  // only play the sound if it is not already playing:
  if(!playFlashRaw1.isPlaying()) {
    playFlashRaw1.play(filename);
    delay(5); // short delay for the audio library
  }

}

// A custom function to play second audio file:
void playRaw2(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);

  // only play the sound if it is not already playing:
  if(!playFlashRaw2.isPlaying()) {
    playFlashRaw2.play(filename);
    delay(5); // short delay for the audio library
  }

}

void loop() {
  mainTimer = millis();
  // Start a sample:
  playRaw1("loop1.raw");

  if((mainTimer - sample2Test) >= sample2Int) {
    sample2Test = millis();
    playRaw2("loop2.raw");
  }

  // Granulate:
  if((mainTimer - granTest) >= granInt) {
    granTest = millis();
    granular1.beginFreeze(random(150)+50);
    granular1.setSpeed(1.0);
  }

}
