#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

//define the symbols on the buttons of the keypads
char Keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

const int redLed = 11;
const int greenLed = 10;
const int blueLed = 9;

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,12};
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(Keys),rowPins,colPins,ROWS,COLS);

void setup()
{
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  Serial.begin(9600);
  Serial.println("Please press the keyboard:");
}

void  loop()
{
  char key = customKeypad.getKey();
  if(key!=NO_KEY)
  {
    Serial.print("Key Value : ");
    Serial.println(key);
    if(key == 'A'){
      digitalWrite(redLed,LOW);
      delay(250);
    }
        if(key == 'B'){
      digitalWrite(greenLed,LOW);
      delay(250);
    }
        if(key == 'C'){
      digitalWrite(blueLed,LOW);
      delay(250);
    }
  }
  else {
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,HIGH);
    digitalWrite(blueLed,HIGH);
  }
}
