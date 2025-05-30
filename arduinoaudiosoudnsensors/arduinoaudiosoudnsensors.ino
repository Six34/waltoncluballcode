#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"
#include <HCSR04.h>

const byte triggerPin = 4;
const byte echoPin = 5;

TMRpcm tmrpcm;

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup() {
tmrpcm.speakerPin=9;
Serial.begin(9600);
if(!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
}

void loop() {
 float distance = distanceSensor.measureDistanceCm();
 Serial.println(distance);
 if (distance <= 15) {
  Serial.println(distance);
  Serial.println("Distance <= 15");
  tmrpcm.setVolume(5.5);
  tmrpcm.play("abcd.wav");
 } else {
  Serial.println(distance);
 }
 delay(1500);
}
