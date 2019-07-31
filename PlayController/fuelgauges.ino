void animate_fuel(int vSF,int vLF,int vOX,int vEL,int vMP)
{  
  //Fuel Gauges
//  vSF = 20; //percentage of solid fuel remaining
//  vLF = 30; //percentage of liquid fuel remaining in current stage
//  vOX = 40; //percentage of oxidized remaining in current stage
//  vEL = 50; //percentage of electric charge remaining
//  vMP = 60; //percentage of monopropellant remaining

  //scale down to 0-9 for binary calculations
  SF = constrain(map(vSF, 100, 0, 0, 9), 0, 9);
  LF = constrain(map(vLF, 100, 0, 0, 9), 0, 9);
  OX = constrain(map(vOX, 100, 0, 0, 9), 0, 9);
  EL = constrain(map(vEL, 0, 100, 0, 9), 0, 9); //EL bar soldered wrong way around
  MP = constrain(map(vMP, 100, 0, 0, 9), 0, 9);

  //calculate the power of 2. Now each value in binary is all zeroes an a single 1. we can use that to light one LED in each LED bar (dot mode)
  int powOX = 0.1+pow(2,OX);
  int powEL = 0.1+pow(2,EL);
  int powMP = 0.1+pow(2,MP);
  int powSF = 0.1+pow(2,SF);
  int powLF = 0.1+pow(2,LF);

  //map the 8-bit 595 shift registers to the 10-bit LED bars, specific to the way I wired them
  inputBytes[0] = powSF >> 6;
  inputBytes[1] = (powSF << 2) | (powLF >> 8);
  inputBytes[2] = powLF;
  inputBytes[3] = powEL >> 3;
  bitWrite(inputBytes[3], 0, bitRead(powEL, 4)); //fix the skipped 595 pin
  inputBytes[4] = (powEL << 4) | (powMP >> 6);
  inputBytes[5] = (powMP << 2) | (powOX >> 8);
  inputBytes[6] = powOX;

  
  //prepare the shift register
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);

  //loop through the input bytes
  for (int j=0; j<=6; j++){
    byte inputByte = inputBytes[j];
    Serial.println(inputByte);
    shiftOut(dataPin, clockPin, MSBFIRST, inputByte);
  }
  
  //latch the values in when done shifting
  digitalWrite(latchPin, HIGH);
}
