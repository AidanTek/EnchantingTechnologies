
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <NXPMotionSense.h>
#include <Wire.h>
#include <EEPROM.h>

NXPMotionSense imu;
NXPSensorFusion filter;

// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  playFlashRaw3;  //xy=238,403
AudioPlaySerialflashRaw  playFlashRaw4;  //xy=238,438
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=239,333
AudioPlaySerialflashRaw  playFlashRaw2;  //xy=239,368
AudioMixer4              mixer1;         //xy=415,386
AudioOutputAnalog        dac1;           //xy=547,386
AudioConnection          patchCord1(playFlashRaw3, 0, mixer1, 2);
AudioConnection          patchCord2(playFlashRaw4, 0, mixer1, 3);
AudioConnection          patchCord3(playFlashRaw1, 0, mixer1, 0);
AudioConnection          patchCord4(playFlashRaw2, 0, mixer1, 1);
AudioConnection          patchCord5(mixer1, dac1);
// GUItool: end automatically generated code


uint8_t ampEnable = 5; // This pin enables the amplifier when HIGH
uint8_t flashSelect = 6; // This pin is the flash chip select

const char* sounds[5] = {"vib1.raw", "vib2.raw", "vib3.raw", "vib4.raw", "vib5.raw"};

void setup() {
  Serial.begin(115200);

//  // NOTE: if you want to use the Serial Monitor, uncomment the next line:
//  while(!Serial);

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

  // set up the mixer channels with a default volume:
  mixer1.gain(0, 0.5); // channel 0 to 3, range 0. to 1. (or greater for amplification)
  mixer1.gain(1, 0.5); // channel 0 to 3, range 0. to 1. (or greater for amplification)
  mixer1.gain(2, 0.5); // channel 0 to 3, range 0. to 1. (or greater for amplification)
  mixer1.gain(3, 0.5); // channel 0 to 3, range 0. to 1. (or greater for amplification)
  
  imu.begin();
  filter.begin(10);
}

// IMU sensor function:
void IMU() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
//  float roll, pitch, heading;

  if (imu.available()) {
    // Read the motion sensors
    imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Update the SensorFusion filter
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

//    // print the heading, pitch and roll
//    roll = filter.getRoll();
//    pitch = filter.getPitch();
//    heading = filter.getYaw();
//    Serial.print("Orientation: ");
//    Serial.print(heading);
//    Serial.print(" ");
//    Serial.print(pitch);
//    Serial.print(" ");
//    Serial.println(roll);
  }
  
//  // Check Accelerometer:
//  printSens(ax, ay, az);

//  // Check Gyrometer:
//  printSens(gx, gy, gz);

//  // Check Magnetometer:
//  printSens(mx, my, mz);

  tapTest(gx, gy, gz);
}

// Use to print data:
void printSens(float x, float y, float z) {
  Serial.print("X = ");
  Serial.print(x);
  Serial.print(" || ");
  Serial.print("Y = ");
  Serial.print(y);
  Serial.print(" || ");
  Serial.print("Z = ");
  Serial.println(z);
}

// Use gyrometer to test for a tap
float lastGX = 0.;
float lastGY = 0.;
float lastGZ = 0.;
uint32_t tapTimeTest;
bool tap;
uint16_t timeDelay = 500;
float gSens = 30.0; // gyrometer sensitivity
uint8_t counter;
void tapTest(float x, float y, float z) {
  uint32_t mainTime;
  mainTime = millis();
  
  if(x < (lastGX-gSens) || x > (lastGX+gSens)) {
    if((mainTime - tapTimeTest) >= timeDelay) {
      tapTimeTest = millis();
      //lastGX = x;
      tap = 1;
    }
  }
  else if(y < (lastGY-gSens) || y > (lastGY+gSens)) {
    if((mainTime - tapTimeTest) >= timeDelay) {
      tapTimeTest = millis();
      //lastGY = y;
      tap = 1;
    }
  }
  else if(z < (lastGZ-gSens) || z > (lastGZ+gSens)) {
    if((mainTime - tapTimeTest) >= timeDelay) {
      tapTimeTest = millis();
      //lastGZ = z;
      tap = 1;
    }
  }
  
  if(tap) {
    Serial.println("Tap!");
    playRaw(sounds[random(4)]);
    tap = 0;
  } 
}


// A custom function to play up to 4 audio files:
void playRaw(const char *filename) {
  // only play the sound if it is not already playing:
  if(!playFlashRaw1.isPlaying()) {
    Serial.print("Playing file: ");
    Serial.println(filename);
    playFlashRaw1.play(filename);
    delay(5); // short delay for the audio library
  }
  else if(!playFlashRaw2.isPlaying()) {
    Serial.print("Playing file: ");
    Serial.println(filename);
    playFlashRaw2.play(filename);
    delay(5); // short delay for the audio library
  }
  else if(!playFlashRaw3.isPlaying()) {
    Serial.print("Playing file: ");
    Serial.println(filename);
    playFlashRaw3.play(filename);
    delay(5); // short delay for the audio library
  }
  else if(!playFlashRaw4.isPlaying()) {
    Serial.print("Playing file: ");
    Serial.println(filename);
    playFlashRaw4.play(filename);
    delay(5); // short delay for the audio library
  }
  else {
    if(counter == 0) {
      Serial.println("Kill file 1");
      playFlashRaw1.stop();
      delay(5);
      Serial.print("Playing file: ");
      Serial.println(filename);
      playFlashRaw1.play(filename);
      delay(5); // short delay for the audio library
      counter++;
    }
    else if(counter == 1) {
      Serial.println("Kill file 2");
      playFlashRaw2.stop();
      delay(5);
      Serial.print("Playing file: ");
      Serial.println(filename);
      playFlashRaw2.play(filename);
      delay(5); // short delay for the audio library
      counter++;
    }
    else if(counter == 2) {
      Serial.println("Kill file 3");
      playFlashRaw3.stop();
      delay(5);
      Serial.print("Playing file: ");
      Serial.println(filename);
      playFlashRaw3.play(filename);
      delay(5); // short delay for the audio library
      counter++;
    }
    else if(counter == 3) {
      Serial.println("Kill file 4");
      playFlashRaw4.stop();
      delay(5);
      Serial.print("Playing file: ");
      Serial.println(filename);
      playFlashRaw4.play(filename);
      delay(5); // short delay for the audio library
      counter = 0;
    }
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  IMU();
  delay(100);  

}
