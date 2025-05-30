#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#include <HCSR04.h>



const byte TRIG_DOOR = 4;
const byte ECHO_DOOR = 5;

const byte TRIG_STAIRS = 6;
const byte ECHO_STAIRS = 7;

const byte SPEAKER_PIN = 9;
const byte SD_ChipSelectPin = 10;

TMRpcm tmrpcm;

UltraSonicDistanceSensor doorSensor(TRIG_DOOR, ECHO_DOOR);
UltraSonicDistanceSensor stairsSensor(TRIG_STAIRS, ECHO_STAIRS);


void setup() {
Serial.begin(9600);

// speaker init
tmrpcm.speakerPin = SPEAKER_PIN;

// sd init
if(!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
}


void loop() {
  float dor = doorSensor.measureDistanceCm();
  float st = stairsSensor.measureDistanceCm();
  
  bool door_trig = false;
  bool stairs_trig = false;
  if (dor <= 20 && dor > 5) {
    //  Serial.println(dor);
    door_trig = true;
  }

  if (st <= 20 && st > 5) {
    // Serial.println(st);
    stairs_trig = true;
  }

  if (door_trig && !stairs_trig){
    // Serial.println("INSIDE");
    // Serial.println(door_trig);
    // Serial.println(stairs_trig);
    
    tmrpcm.setVolume(5.5);
    tmrpcm.play("abcd.wav");
    
    delay(2000);
  } else {

    door_trig = false;
    stairs_trig = false;
    
    // Serial.println("ELSE");
    // Serial.println(door_trig);
    // Serial.println(stairs_trig);

    delay(2000);
  }
}
