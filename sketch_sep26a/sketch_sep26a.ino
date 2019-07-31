#include <math.h>

//segments of the display (a through g), shared by each digit
const int a = 6; //pin 13 on the display
const int b = 7; //pin 9 on the display
const int c = 8; //pin 4 on the display
const int d = 9; //pin 2 on the display
const int e = 10; //pin 1 on the display
const int f = 11; //pin 12 on the display
const int g = 12; //pin 5 on the display
const int segments[] = {a, b, c, d, e, f, g};
const int numSegments = 7;

//digital point segment (also shared by each digit)
const int dp = 13; //pin 3 on the display

//digits of the display (1 through 4), note pins 7 and 8 on ther display are left unused (colon)
const int d1 = 2; //pin 14 on the display
const int d2 = 3; //pin 11 on the display
const int d3 = 4; //pin 10 on the display
const int d4 = 5; //pin 6 on the display
const int digits[] = {d1, d2, d3, d4};
const int numDigits = 4;

//status LEDs used to indicate the phase
const int led1 = A3;
const int led2 = A4;
const int led3 = A5;
const int led0 = A0;

//input pins
const int potVoltage = A2; //output voltage of pot meter
const int button = A1; //pushbutton

//variables
long rawInput = 0; //variable to hold the input values
int buttonState = 1;
int prevButtonState = 1;
int phase = 0;
long ISP;
long wetmass;
long drymass;
long deltav;

//how to turn on a digit (common cathode)
#define ON LOW
#define OFF HIGH

//timing
const int segmentDelay = 500;
const int digitDelay = 500;

//scaling
const float ISPscale = 20000000; //0.78357;  //maximum ISP = 800
const float wetmassscale = 2; //0.196;  //maximum wet mass = 200
const float drymassscale = 0.147;  //maximum dry mass = 150

///////////////
//setup section
///////////////
void setup() {
  //setup pin modes
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  for (int i = 0; i < numSegments; i++) {
    pinMode(segments[i], OUTPUT);
  pinMode(dp, OUTPUT);
  }
  for (int j = 0; j < numDigits; j++) {
    pinMode(digits[j], OUTPUT);
  }
  
  //turn all digits off
  for (int j = 0; j < numDigits; j++) {
    digitalWrite(digits[j], OFF);
  }
 
  //start serial for debugging
  Serial.begin(9600);
}

///////////
//main loop
///////////
void loop() {

  for (long i = 1; i > 0; ){
    displayNumber(i);
    i = 10 * i;
    Serial.println(i);
    delay(1000);
  }
}

/////////////////
//functions below
/////////////////

// Function to display numbers between 0 and 9.9E9 on the 4-digit display
void displayNumber (long input_number) {

  if (input_number > 9999999999) {
    //number too large to display, even in scientific notation
    displaySingle(11, 0, false);
    displaySingle(11, 1, false);
    displaySingle(11, 2, false);
    displaySingle(11, 3, false);
  }
  if ((input_number < 9999999999) && (input_number > 999999999)) {
    //display format a.bE9
    int a = ((input_number - (input_number % 1000000000)) - (input_number - (input_number % 10000000000)))/1000000000;
    int b = ((input_number - (input_number % 100000000)) - (input_number - (input_number % 1000000000)))/100000000;
    displaySingle(a, 0, true);
    displaySingle(b, 1, false);
    displaySingle(11, 2, false);
    displaySingle(9, 3, false);
  }
  if ((input_number < 999999999) && (input_number > 99999999)) {
    //display format b.cE8
    int b = ((input_number - (input_number % 100000000)) - (input_number - (input_number % 1000000000)))/100000000;
    int c = ((input_number - (input_number % 10000000)) - (input_number - (input_number % 100000000)))/10000000;
    displaySingle(b, 0, true);
    displaySingle(c, 1, false);
    displaySingle(11, 2, false);
    displaySingle(8, 3, false);
  }
  if ((input_number < 99999999) && (input_number > 9999999)) {
    //display format c.dE7
    int c = ((input_number - (input_number % 10000000)) - (input_number - (input_number % 100000000)))/10000000;
    int d = ((input_number - (input_number % 1000000)) - (input_number - (input_number % 10000000)))/1000000;
    displaySingle(c, 0, true);
    displaySingle(d, 1, false);
    displaySingle(12, 2, false);
    displaySingle(7, 3, false);
  }
  if ((input_number < 9999999) && (input_number > 999999)) {
    //display format d.eE6
    int d = ((input_number - (input_number % 1000000)) - (input_number - (input_number % 10000000)))/1000000;
    int e = ((input_number - (input_number % 100000)) - (input_number - (input_number % 1000000)))/100000;
    displaySingle(d, 0, true);
    displaySingle(e, 1, false);
    displaySingle(11, 2, false);
    displaySingle(6, 3, false);
  }
  if ((input_number < 999999) && (input_number > 99999)) {
    //display format e.fE5
    int e = ((input_number - (input_number % 100000)) - (input_number - (input_number % 1000000)))/100000;
    int f = ((input_number - (input_number % 10000)) - (input_number - (input_number % 100000)))/10000;
    displaySingle(e, 0, true);
    displaySingle(f, 1, false);
    displaySingle(11, 2, false);
    displaySingle(5, 3, false);
  }
  if ((input_number < 99999) && (input_number > 9999)) {
    //display format f.gE4
    int f = ((input_number - (input_number % 10000)) - (input_number - (input_number % 100000)))/10000;
    int g = ((input_number - (input_number % 1000)) - (input_number - (input_number % 10000)))/1000;
    displaySingle(f, 0, true);
    displaySingle(g, 1, false);
    displaySingle(11, 2, false);
    displaySingle(4, 3, false);
  }
  if ((input_number < 9999) && (input_number > 999)) {
    //display format ghij
    int g = ((input_number - (input_number % 1000)) - (input_number - (input_number % 10000)))/1000;
    int h = ((input_number - (input_number % 100)) - (input_number - (input_number % 1000)))/100;
    int i = ((input_number - (input_number % 10)) - (input_number - (input_number % 100)))/10;
    int j = ((input_number - (input_number % 1)) - (input_number - (input_number % 10)))/1;
    displaySingle(g, 0, false);
    displaySingle(h, 1, false);
    displaySingle(i, 2, false);
    displaySingle(j, 3, false);
  }
  if ((input_number < 999) && (input_number > 99)) {
    //display format _hij
    int h = ((input_number - (input_number % 100)) - (input_number - (input_number % 1000)))/100;
    int i = ((input_number - (input_number % 10)) - (input_number - (input_number % 100)))/10;
    int j = ((input_number - (input_number % 1)) - (input_number - (input_number % 10)))/1;
    displaySingle(10, 0, false);
    displaySingle(h, 1, false);
    displaySingle(i, 2, false);
    displaySingle(j, 3, false);
  }
  if ((input_number < 99) && (input_number > 9)) {
    //display format __ij
    int i = ((input_number - (input_number % 10)) - (input_number - (input_number % 100)))/10;
    int j = ((input_number - (input_number % 1)) - (input_number - (input_number % 10)))/1;
    displaySingle(10, 0, false);
    displaySingle(10, 1, false);
    displaySingle(i, 2, false);
    displaySingle(j, 3, false);
  }
  if ((input_number < 9) && (input_number >= 1)) {
    //display format ___j
    int j = ((input_number - (input_number % 1)) - (input_number - (input_number % 10)))/1;
    displaySingle(10, 0, false);
    displaySingle(10, 1, false);
    displaySingle(10, 2, false);
    displaySingle(j, 3, false);
  }
  if ((input_number < 1) && (input_number >= 0)) {
    //display format 0
    displaySingle(10, 0, false);
    displaySingle(10, 1, false);
    displaySingle(10, 2, false);
    displaySingle(10, 3, false);
  }
}

void displaySingle(int numberShown, int numPosition, bool point) {

  //define which segments to turn on to show a specific number
  const int numbers[12][7] = {
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, //zero
    {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},  //one
    {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},  //two
    {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},  //three
    {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},  //four
    {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},  //five
    {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},  //six
    {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},  //seven
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},  //eight
    {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH},  //nine
    {LOW, LOW, LOW, LOW, LOW, LOW, LOW},  //blank
    {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH}  //E
    
    
  };

  //loop through all segments
  for (int i = 0; i < numSegments; i++) {
    //turn on segments needed for this number
    digitalWrite(segments[i], numbers[numberShown][i]);
  }
  //digital point
  if (point == true){digitalWrite(dp, HIGH);}
  else {digitalWrite(dp, LOW);}
  
  //turn on the digit requested for a short time
  digitalWrite(digits[numPosition], ON);
  delay(digitDelay);
  digitalWrite(digits[numPosition], OFF);
}


