char val;
boolean ledState = LOW;
boolean buttonState;

const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(A7, INPUT);
  establishContact();
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void establishContact() {
  //keep sending A until a first response is received
  while (Serial.available() <= 0) {
    Serial.println("A");
    delay(300);
  }
  //as soon as a first response is received, we break out of the while loop and into the main program loop
}

void loop() {
  if (Serial.available() > 0) {
    //serial data is coming in
    val = Serial.read();
    if (val == '1') {
      ledState = !ledState;
      digitalWrite(13, ledState);
    }
    delay(100);
  } else {
    //no serial data received, so time to send some data out
    //    buttonState = digitalRead(8);
    //    if(buttonState == LOW){
    //      Serial.println("10");
    //    }
    //    if(buttonState == HIGH){
    //      Serial.println("100");
    //    }
      // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(A7);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
    Serial.println(average);
    delay(50);
  }
}
