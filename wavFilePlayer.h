#include <Audio.h>
// #include <Wire.h> // already in mpr121.h
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav4;     //xy=246,418
AudioPlaySdWav           playSdWav3;     //xy=248,366
AudioPlaySdWav           playSdWav2;     //xy=250,322
AudioPlaySdWav           playSdWav1;     //xy=251,275
AudioMixer4              mixer1;         //xy=687,408
AudioMixer4              mixer2;         //xy=698,536
AudioOutputI2S           i2s1;           //xy=1095,733
AudioConnection          patchCord1(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord2(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord3(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord4(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord5(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord6(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord7(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord8(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord9(mixer1, 0, i2s1, 0);
AudioConnection          patchCord10(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=842,836
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

void init_player() {

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playSdWav1.play(filename);

  // // A brief delay for the library read WAV info
  // delay(5);

  // // Simply wait for the file to finish playing.
  // while (playWav1.isPlaying()) {
  //   // uncomment these lines if you audio shield
  //   // has the optional volume pot soldered
  //   //float vol = analogRead(15);
  //   //vol = vol / 1024;
  //   // sgtl5000_1.volume(vol);
  // }
}


// void loop() {
//   playFile("SDTEST1.WAV");  // filenames are always uppercase 8.3 format
//   delay(500);
//   playFile("SDTEST2.WAV");
//   delay(500);
//   playFile("SDTEST3.WAV");
//   delay(500);
//   playFile("SDTEST4.WAV");
//   delay(1500);
// }
