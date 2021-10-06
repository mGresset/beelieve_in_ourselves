const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  int8_t value = map(sensorValue, 867, 982, 0, 100);
  //int8_t val_volt = 4,2/1023*value;

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(value);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);
}
