
const int buttonPin = D2;     
const int ledPin =  D0;      

// variables will change:
int buttonData = 0;      

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonData = digitalRead(buttonPin);
  if (buttonData == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
