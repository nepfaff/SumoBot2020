int xAxis, yAxis;
void setup() {
  Serial.begin(38400);
}
void loop() {
  xAxis = analogRead(A0); // Read Joysticks X-axis
  yAxis = analogRead(A1); // Read Joysticks Y-axis

  //for testing only:
  /*Serial.print("xAxis: ");
  Serial.println(xAxis);
  Serial.print("yAxis: ");
  Serial.println(yAxis);*/
  
  // Send the values via the serial port to the slave HC-05 Bluetooth device
  //Serial.write(xAxis/4); // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  //Serial.write(yAxis/4);
  delay(20);
  //delay(1000);

  //Serial.print("Info: ");
  //Serial.println(Serial.available());
}
