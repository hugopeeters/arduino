const int latchPin = 8; //ST_CP
const int clockPin = 12; //SH_CP
const int dataPin = 11; //DS

byte data1;
byte data2;
byte data3;
byte data4;
byte data5;
byte data6;
byte data7;

//mock data
int64_t inputvalue = 123; //decimal representation of 50-bit number

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {

  //prepare the shift register
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);

  //loop through the input bits
  for (int i=50; i>=0; i--){
    //clock low
    digitalWrite(clockPin, LOW);
    //shift the bit out
    digitalWrite(dataPin, (bitRead(inputvalue, i)));
    //pulse the clock high
    digitalWrite(clockPin, HIGH);
    //set the data pin low to prevent bleed through
    digitalWrite(dataPin, LOW);
    //end clock pulse
    digitalWrite(clockPin, LOW);
  }
  
  //latch the values in when done shifting
  digitalWrite(latchPin, HIGH);

  delay(300);
}
