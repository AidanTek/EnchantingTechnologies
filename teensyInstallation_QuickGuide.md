# Teensy Installation Quick Guide

This document is a quick guide to get started with the Teensy platform. All the tools are free!

---

### Install/Update Arduino

* First make sure you have the latest version of the Arduino IDE installed for your OS - this can be downloaded from the [Arduino site](https://www.arduino.cc/en/Main/Software)
* Make sure Arduino is properly installed, this is usually as simple as unzipping the download, but make sure the Arduino app is kept in a sensible directory like **Applications** on Mac OS, don't leave it in downloads as it can quickly get confusing next time you update!
* Open Arduino for the first time, this will create the libraries directory which can usually be found in your home **Documents** directory.

---

### Install Teensyduino
Teensyduino is a free tool provided by PJRC - it configures your Arduino IDE to include the Teensy firmware and libraries. It also installs the Teensy Loader application that acts as a bridge between the Arduino IDE and Teensy hardware when uploading.

* Navigate to the [PJRC website](https://www.pjrc.com/teensy/td_download.html) Teensyduino page and download the package for your OS
* Once the package has downloaded, open it and run the installer
* Follow the instructions, you will be asked to point the installer to your Arduino IDE application
* I normally leave the additional libraries checked - they won't take up any significant space on your computer, follow the steps to complete the installation

On Linux, Teensyduino is only supported for Ubuntu distributions. There are some additional steps required to get things working smoothly:

In order to run the installer at all, you need to change the permissions, use a terminal emulator to navigate to the directory you placed the installer in and run the following command (adjust to the correct version if necessary):
```
chmod 755 TeensyduinoInstall.linux32
```

You need to add udev rules in order to use Teensy devices, download the file from the PJRC link above and then run this command in the directory you download to:
```
sudo cp 49-teensy.rules /etc/udev/rules.d/
```

Now you can run the installer with (adjust as necessary):
```
./TeensyduinoInstall.linux32
```

---

### Test!
Open Arduino, you should find that you have a selection of new Teensy boards and a boatload of examples to go with it.

* Navigate to **Tools>Boards** and select **Teensy 3.2/3.1**
* Navigate to **File>Examples>01 Basics** and select **Blink**
* With your hardware connected, upload the sketch to the Teensy
* You should see the Teensyduino app automatically open, and it will have it's own progress bar as it uploads the sketch to the Teensy

If everything goes off without a hitch then you are set!

---

If you encounter any problems using this tutorial, please contact me and I will update this document as soon as possible 
