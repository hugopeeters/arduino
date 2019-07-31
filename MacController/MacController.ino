char val;
boolean ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  establishContact();
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();
    if (val == '1') {
      ledState = !ledState;
      digitalWrite(13, ledState);
    }
    delay(100);
  } else {
    Serial.println("Hello World!");
    delay(50);
  }
}

void establishContact(){
  while (Serial.available() <= 0){
    Serial.println("A");
    delay(300);
  }
}
