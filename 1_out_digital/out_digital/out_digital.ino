const int PIN_LED = D0;
const int PIN_LED1 = D1;

void setup() {
  
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_LED1, HIGH); 
  delay(1000);              
  digitalWrite(PIN_LED, LOW);   
  digitalWrite(PIN_LED1, LOW);
  delay(1000);           
}
