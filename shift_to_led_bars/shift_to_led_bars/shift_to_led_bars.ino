const int latchPin = 8; //ST_CP - green
const int clockPin = 12; //SH_CP - blue
const int dataPin = 11; //DS - yellow

byte inputBytes[7];

int vSF, vLF, vOX, vEL, vMP, SF, LF, OX, EL, MP;
void setup() {

Serial.begin(9600);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  

}

void loop() {
  vSF = 100;
  vLF = 100;
  vOX = 100;
  vEL = 100;
  vMP = 100;

  SF = constrain(map(vSF, 100, 0, 0, 9), 0, 9);
  LF = constrain(map(vLF, 100, 0, 0, 9), 0, 9);
  OX = constrain(map(vOX, 100, 0, 0, 9), 0, 9);
  EL = constrain(map(vEL, 0, 100, 0, 9), 0, 9);
  MP = constrain(map(vMP, 100, 0, 0, 9), 0, 9);
  
  Serial.print(SF);
  Serial.print(",");
  Serial.print(LF);
  Serial.print(",");
  Serial.print(OX);
  Serial.print(",");
  Serial.print(EL);
  Serial.print(",");
  Serial.println(MP);

  int pOX = 0.1+pow(2,OX);
  int pEL = 0.1+pow(2,EL);
  int pMP = 0.1+pow(2,MP);
  int pSF = 0.1+pow(2,SF);
  int pLF = 0.1+pow(2,LF);
  
  Serial.print(pSF);
  Serial.print(",");
  Serial.print(pLF);
  Serial.print(",");
  Serial.print(pOX);
  Serial.print(",");
  Serial.print(pEL);
  Serial.print(",");
  Serial.print(pMP);
  Serial.println();
  
  inputBytes[0] = pSF >> 6;
  inputBytes[1] = (pSF << 2) | (pLF >> 8);
  inputBytes[2] = pLF;
  inputBytes[3] = pEL >> 3;
  bitWrite(inputBytes[3], 0, bitRead(pEL, 4)); //fix the skipped 595 pin
  inputBytes[4] = (pEL << 4) | (pMP >> 6);
  inputBytes[5] = (pMP << 2) | (pOX >> 8);
  inputBytes[6] = pOX;


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
  delay(30000);
}
