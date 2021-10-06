const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  //int8_t value = map(sensorValue, 63, 975, 0, 100);
  float val_volt = sensorValue*3.3/1023;

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.println(val_volt);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);
}
