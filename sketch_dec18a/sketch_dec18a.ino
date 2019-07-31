
//segments
const int a = 10;
const int b = 8;
const int c = 3;
const int d = 5;
const int e = 6;
const int f = 9;
const int g = 2;
const int segments[] = {a, b, c, d, e, f, g};
const int numSegments = 7;

//digits
const int d1 = 4;
const int d2 = 13;
const int d3 = 12;
const int d4 = 11;
const int digits[] = {d1, d2, d3, d4};
const int numDigits = 4;

#define ON LOW
#define OFF HIGH

//colon
const int col = 7;

int segmentDelay = 50;
int digitDelay = 500;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < numSegments; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (int j = 0; j < numDigits; j++) {
    pinMode(digits[j], OUTPUT);
  }
  pinMode(col, OUTPUT);

  //all digits off
  for (int j = 0; j < numDigits; j++) {
    digitalWrite(digits[j], OFF);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //test
  for (int j = 0; j < numDigits; j++) {
    digitalWrite(digits[j], ON);

    for (int i = 0; i < numSegments; i++) {
      digitalWrite(segments[i], HIGH);
      delay(segmentDelay);
      digitalWrite(segments[i], LOW);
    }
    delay(digitDelay);
    digitalWrite(digits[j], OFF);

  }
  digitalWrite(col, HIGH);
  delay(digitDelay);
  digitalWrite(col, LOW);
}

void displayNumbers(int n1, int n2, int n3, int n4, bool col){
  
}

