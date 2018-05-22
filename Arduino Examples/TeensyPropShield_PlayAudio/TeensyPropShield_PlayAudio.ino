/* 
Fab-Cre8 Enchanting Technologies 

Teensy Prop Shield Example: Audio File Playback

I used the online "Audio System Design Tool" provided by pjrc to set up the audio interface: https://www.pjrc.com/teensy/gui/

Prerequisites:
- Teensyduino must be installed, see here for details on how to install on your system: https://www.pjrc.com/teensy/td_download.html
- Audio must be on the Prop Shield, please see the notes in the Repository on this.
- Speaker attached to the output of the Prop Shield
- Select "Teensy 3.2/3.1" from the Boards menu and "Serial" from the USB Type menu (both are found under tools)

Example by Aidan Taylor 2018.
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=161,239
AudioMixer4              mixer1;         //xy=322,258
AudioOutputAnalog        dac1;           //xy=455,258
AudioConnection          patchCord1(playFlashRaw1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, dac1);
// GUItool: end automatically generated code

uint8_t ampEnable = 5; // This pin enables the amplifier when HIGH
uint8_t flashSelect = 6; // This pin is the flash chip select

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

  // set up the mixer with a default volume:
  mixer1.gain(0, 0.8); // channel 0 to 3, range 0. to 1. (or greater for amplification)
}

// A custom function to play an audio file:
void playRaw(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);

  // only play the sound if it is not already playing:
  if(!playFlashRaw1.isPlaying()) {
    playFlashRaw1.play(filename);
    delay(5); // short delay for the audio library
  }

}

void loop() {
  // use the playRaw function with the filename (string) as included argument:
  playRaw("01.raw");

  delay(5000); // The audio library works asyncronously, so it is fine to use a delay here
}
