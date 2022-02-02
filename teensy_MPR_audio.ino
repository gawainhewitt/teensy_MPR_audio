/*
Simple arduino sketch to show four MPR121 boards working at the same time and then triggering wav files using the
Teensy Audio shield on a Teensy 4

On the MPR121 remember to set the address pins.

As standard address is tied to Ground which gives the default address of 0x5A

To use the other three available channels you need to cut the address pad in the middle and then connect address to the following:

Connect address to 3.3v for 0x5B
Connect address to SDA for 0x5C
Connect address to SCL for 0x5D

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include "mpr121.h"
#include "wavFilePlayer.h"
#include "reboot.h"

const int rebootButton = 9;

void setup() {
Serial.begin(9600);
init_mpr121();
init_player();
pinMode(rebootButton, INPUT_PULLUP);

}

void loop() {
currtouched1 = mprBoard_A.touched();
currtouched2 = mprBoard_B.touched();
currtouched3 = mprBoard_C.touched();
// currtouched4 = mprBoard_D.touched();

if(digitalRead(rebootButton) == LOW){
    doReboot();
}

//For A----------------------------------------------------------
for (uint8_t i=0; i<12; i++) {
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
    Serial.print(i); Serial.println(" touched of A");

    playSdWav1.play("SDTEST1.WAV"); // filenames are always uppercase 8.3 format
    }

    if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
    Serial.print(i); Serial.println(" released of A");
    playSdWav1.stop();
    }


    //For B----------------------------------------------------------
    if ((currtouched2 & _BV(i)) && !(lasttouched2 & _BV(i)) ) {
    Serial.print(i); Serial.println(" touched of B");

    playSdWav2.play("SDTEST2.WAV");
    }

    if (!(currtouched2 & _BV(i)) && (lasttouched2 & _BV(i)) ) {
    Serial.print(i); Serial.println(" released of B");
    playSdWav2.stop();
    }


    //For C----------------------------------------------------------
    if ((currtouched3 & _BV(i)) && !(lasttouched3 & _BV(i)) ) {
    Serial.print(i); Serial.println(" touched of C");

    playSdWav3.play("SDTEST3.WAV");
    }

    if (!(currtouched3 & _BV(i)) && (lasttouched3 & _BV(i)) ) {
    Serial.print(i); Serial.println(" released of C");
    playSdWav3.stop();
    }

    // //For D----------------------------------------------------------
    // if ((currtouched4 & _BV(i)) && !(lasttouched4 & _BV(i)) ) {
    // Serial.print(i); Serial.println(" touched of D");

    // playSdWav4.play("SDTEST4.WAV");
    // }

    // if (!(currtouched4 & _BV(i)) && (lasttouched4 & _BV(i)) ) {
    // Serial.print(i); Serial.println(" released of D");
    // playSdWav4.stop();
    // }
}

lasttouched1 = currtouched1;
lasttouched2 = currtouched2;
lasttouched3 = currtouched3;
// lasttouched4 = currtouched4;
return;
}
