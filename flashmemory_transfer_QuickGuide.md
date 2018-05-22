# Prop Shield Flash Memory Transfer

This is a guide to transfering audio files to the flash memory on the Prop Shield. Sorry it is all text, but once you have installed and done things once you will see it is easy.

---

### Important notes:
* Flash memory is limited to 8MByte, you can have as many audio samples as you want but can't exceed this.
* Audio should be in WAV or RAW format - RAW is actually more efficient for this application, but is a less standard compression type so there are less standard tools that deal with it. Files must be 16bit @ 44.1kHz or they will not sound right (n.b this gives you about 40 seconds of WAV audio) **Further note on this:** *I can't find any information on WAV playback from flash memory - I recommend you convert to RAW. Teensy recommends the [SoX](http://sox.sourceforge.net/) tool which works on any OS*
* Frank Boesing's TeensyTransfer CLI tool is required - [clone or download from here](https://github.com/FrankBoesing/TeensyTransfer) (also provided in this repository, please view the included license for correct use)

See the [forum page](https://forum.pjrc.com/threads/33859-TeensyTransfer) for detailed information and discussion on the tool - I went through the pain so you don't have to!

---

### Install Teensy Transfer

* Download Teensy Transfer from the link above, or find it in this repository
* Copy the folder (unzip it if you need to) into your **Arduino Libraries** folder - this is normally located in **Documents** in your home folder
* Navigate into the **TeensyTransfer-master** folder and then into **extras**
* Unzip the package for your operating system

*If you are on Linux you also need to run the following command in your terminal:*
```
chmod +x teensytransfer
```

*I also had to install 32bit USB dependencies:*
```
sudo apt update
sudo apt install libusb-0.1-4i386
```

That's it!

---

### How to transfer files:

Any time you want to change the contents of the flash memory, the Teensy needs to have a utility sketch loaded onto it:

* Open the Arduino IDE
* Make sure that under **Boards** that **Teensy 3.2/3.1** is selected
* Open the sketch **TeensyTransferTool** found under **File>Examples>TeensyTransfer-master** (probably close to the bottom of your list)
* Set **USB Type** under the **Tools** menu to "**Raw HID**"
* Upload this code to the Teensy

Next we use the CLI tool to transfer the files:

* Open a command line tool on your machine. On Mac / Linux use your Terminal emulator, on Windows I recommend you download [PuTTY](https://www.putty.org/)
* Navigate to the directory you unzipped the transfer tool into (cd means change directory), for me this is:

```
cd ~/Arduino/libraries/TeensyTransfer-master/extras
```
* Test the tool first by entering (reports basic information on the device, on Linux you need to use ./teensytransfer with the command below)):
```
teensytransfer -i teensy
```
* Next, erase the contents of the flash memory with:
```
teensytransfer -e
```
* Finally, transfer a file with the command:
```
teensytransfer -w (filepath to file)
```
for example:
```
teensytransfer -w ~/Downloads/mySound.wav
```

Once you have transferred your files you can try the audio player example

### Quick tips:
* Pressing **tab** in most terminal emulators will try to auto-complete the command you are typing - good if you are filling in file paths and for many other things as well
* On Mac OS (this may work on other systems as well) you can drag and drop a file into your terminal emulator, and it will generate the file path
* You can use iTunes to convert audio files reliably, you can change the compression type (doesn't do RAW sadly) and change the sample rate and bit depth - but there are plenty of free tools you can download as well

Please let me know if you run into issues and I will try to keep this file up to date.



