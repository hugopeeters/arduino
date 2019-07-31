int digit1 = 2;
int digit2 = 3;
int digit3 = 4;
int digit4 = 5;
int segmentA = 6;
int segmentB = 7;
int segmentC = 8;
int segmentD = 9;
int segmentE = 10;
int segmentF = 11;
int segmentG = 12;
int segmentDP = 13;

void setup() {
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(segmentDP, OUTPUT);
}

void loop() {
  for (int i = 2; i < 6; i++){
    for (int j = 6; j < 14; j++){
      digitalWrite(i,LOW);
      digitalWrite(j,HIGH);
      delay(100);
      digitalWrite(i,HIGH);
      digitalWrite(j,LOW);
    }
  }
}
