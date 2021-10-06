const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  int8_t value = map(sensorValue, 781, 983, 0, 100);
  float val_volt = sensorValue*4.2/1023;

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(value);
  Serial.println(val_volt);

  delay(1000);
}
