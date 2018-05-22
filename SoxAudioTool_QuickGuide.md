# SoX Audio Tool Quick Guide

There are plenty of free tools out there for audio file conversion. SoX is a CLI tool so the interface is very simple, but as a result of this it is a fast, reliable and simple tool to use.

I recommend that this tool is used to recompress audio files to be suitable for the Teensy Prop Shield's flash memory. If you are not comfortable with CLI commands, you could look into using Audacity as an alternative - but I can't help with this!

---

### Compression for flash memory: 

I only know how to play back audio files with RAW compression at the moment, but this is no real issue and RAW is the recommended type to use. (I'm guessing WAV works as well, but don't know how to build WAV playback into the sketch.

Audio files must have 44.1kHz sample rate and 16 bit depth, or else playback will produce odd results. Don't worry too much if you don't know what these values represent - but it is important to stick to them. For best results use audio that was originally recorded at 44.1kHz and 16bit or higher. 

You can find sounds licensed for free use under Creative Commons at [freesound.org](freesound.org) - registration is required, but you can browse sounds by their compression type, sample rate and bit depth which is handy for our purpose!

---

### Installing SoX

* Navigate to the [SoX project page](http://sox.sourceforge.net/)
* Click on the link to download from source
* Pick the latest version
*More to follow, I'm on Linux sorry!*

On Ubuntu Linux or Ubuntu flavours, use the package manager:
```
sudo apt update
sudo apt install sox
```

---

### Basic usage

SoX is a command line tool, interact with it from a terminal emulator like Terminal on Mac OS / Linux, or PuTTY on Windows.

The most basic usage of SoX is just to convert a file to have a new compression, which can be achieved like this:

```
cd (to your directory storing the audio)
sox oldSound.wav newSound.raw
```

(Alternatively you can use the absolute path to the input and output files)

A new file is created and you can rename it in the process. 

This will maintain the characteristics of the original file (channels, sample rate, bit depth etc), but we can easily change that if we need to by adding some additional arguments to the command:

```
sox audio.wav newAudio.raw channel 1
```
Mixes down to one channel

```
sox audio.wav newAudio.raw -b 16 -r 44100
```
Sets the **-b** bit depth and **-r** sample rate  of the output file

Of course, you can combine as you like:
```
sox audio.wav newAudio.raw channel 1 -b 16 -r 44100
```

That is about everything you need for the Prop Shield flash memory, but feel free to take a look at the [online documentation](http://sox.sourceforge.net/sox.html) to see some of the other useful features of SoX (concatenating multiple audio files and mixing them together, even of different compressions are among the features!)

--- 

If you run into any problems with the above tutorial, please let me know and I will update it as soon as possible.

