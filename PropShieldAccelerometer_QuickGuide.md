# Prop Shield Accelerometer Quick Guide

This is a quick guide to provide some details on use of the Prop Shield accelerometer.

If you have already installed Teensyduino and the associated libraries, you will already have some useful example code. The accelerometer works out of the box but is not calibrated for accuracy - if accuracy is important, follow the instructions below.

---

### Calibration

If you are using one of the Fab-Cre8 Teensy boards with Prop Shield attached, the chances are that I have already calibrated it, so there is no need to do it again.

The accelerometer will not be calibrated initially and there are some tools available to help get more accurate readings. There are instructions on the [Prop Shield store page](https://www.pjrc.com/store/prop_shield.html) to achieve this, it requires an additional app to be installed called MotionCal.

Once you have installed the MotionCal app, open the Arduino IDE and open the sketch under **File>Examples>NXPMotionsense>CalibrateSensors**. Upload the sketch and check the Serial Monitor to make sure that the sensor is sending data. 

Close the serial monitor and open the MotionCal app. Select the port in the MotionCal app that the Teensy is connected to. Turn the Teensy board around on all axis - you will see a shape starting to form in the app, continuing to turn the Teensy will eventually form a globe like structure. Once this is fairly complete, press the **Send Calibration** button - this will store the calibration in the Teensy's EEPROM, so you shouldn't need to do it again.

#####Linux Only:
If you are on an Ubuntu Linux distribution, you will need to change permissions of the MotionCal app. To run it, type the following into your terminal emulator:

```
chmod 755 ./MotionCal.linux64
```

I was also missing a library dependency which took a while to resolve - if you have a "cannot open shared object file" error then first, try to establish what is missing with:
```
ldd ./MotionCal.linux64
```
I was missing a dependency called libpng12.so.0 - after some searching I found this fix worked for me:

```
wget -q -O /tmp/libpng12.deb http://mirrors.kernel.org/ubuntu/pool/main/libp/libpng/libpng12-0_1.2.54-1ubuntu1_amd64.deb \
  && sudo dpkg -i /tmp/libpng12.deb \
  && rm /tmp/libpng12.deb
```
Only do this if you are missing the same library.

---

### Notes on use

I've found the accelerometer to be surprisingly accurate, but not without problems. It seems to be prone to what I would describe as "drift" where the absolute value is gradually changing constantly. I think this is down to temperature stability and also quite possibly the fact that a speaker is in close proximity (it is all based on magnetism after all!)

Absolute direction is good but not perfect, be aware of this - a more meticulous approach to calibration might improve things, but the accelerometer will still work very well for gestures like:

* Any movement at all
* Sudden change in movement
* Sudden change in a specific direction, including twists etc.

---

If you encounter any issues with this guide, please let me know and I will update it as soon as possible.

