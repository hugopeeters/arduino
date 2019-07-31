#include <SPI.h>

int dataPin = 2;
int latchPin = 3;
int clockPin = 4;
int d1Pin = 5;
int d2Pin = 6;
int d3Pin = 7;
int d4Pin = 8;

byte data;
byte dataArray[10];

void setup(){

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(d1Pin, OUTPUT);
  pinMode(d2Pin, OUTPUT);
  pinMode(d3Pin, OUTPUT);
  pinMode(d4Pin, OUTPUT);

  dataArray[0] = 0x00;
  dataArray[1] = B00000001;
  dataArray[2] = 0x02;
  dataArray[3] = 0x04;
  dataArray[4] = 0x08;
  dataArray[5] = 0x10;
  dataArray[6] = 0x20;
  dataArray[7] = 0x40;
  dataArray[8] = 0x80;
  dataArray[9] = 0xFF;

}

void loop(){

  digitalWrite(d1Pin, LOW);
  digitalWrite(d2Pin, HIGH);
  digitalWrite(d3Pin, HIGH);
  digitalWrite(d4Pin, HIGH);
//  digitalWrite(clockPin, LOW);

  for (int j = 0; j < 10; j++) {
    data = dataArray[1];
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, data);
    digitalWrite(latchPin, HIGH);
    delay(300);
  }

}
