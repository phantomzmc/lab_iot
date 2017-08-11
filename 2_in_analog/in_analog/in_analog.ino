

const int analogPin = A0;  // Analog input pin 
int dataA0;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  dataA0 = analogRead(analogPin);
  float voltage = dataA0 * (3.3 / 1023.0);
  // print the results to the serial monitor:
  Serial.print("sensor_data_A0 = ");
  Serial.print(dataA0);
  Serial.print("   volt:"); 
  Serial.println(voltage); 
  delay(500);
}
