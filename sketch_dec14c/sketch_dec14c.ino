
int buttonPin = 2;
int speakerPin = 3;
int redPin = 5;
int greenPin = 6;
int notes[] = {262, 294, 330, 392, 440, 494, 523, 587};
int ledSequence[] = {redPin, greenPin, redPin, greenPin, redPin, greenPin, redPin, greenPin};
int arrayLength = 8;
int delayTime = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);


  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(buttonPin);
  //Serial.print("Button State: ");
  //Serial.println(buttonState);
  //delay(100);
  if (buttonState == 0) {

    //run audio and blink sequence
    for (int i = 0; i < arrayLength - 1; i++) {
      tone(speakerPin, notes[i]);
      digitalWrite(ledSequence[i], HIGH);
      delay(delayTime);
      digitalWrite(ledSequence[i], LOW);
    }

    for (int i = arrayLength - 1 ; i > -1; i--) {
      tone(speakerPin, notes[i]);
      digitalWrite(ledSequence[i], HIGH);
      delay(delayTime);
      digitalWrite(ledSequence[i], LOW);
    }

    //generate random outcome
    float rnd = random(0, 10);
    if (rnd < 5) {
      digitalWrite(greenPin, HIGH);
      tone(speakerPin, 587);
    }
    else {
      digitalWrite(redPin, HIGH);
      tone(speakerPin, 262);

    }
    delay(1000);
  }
  else {
    noTone(speakerPin);
  }
}
