#include <SoftwareSerial.h>
SoftwareSerial BTSerial(3, 11);

#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7
int xAxis, yAxis;
unsigned int  x = 0;
unsigned int  y = 0;
int motorSpeedA = 0;
int motorSpeedB = 0;
void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  BTSerial.begin(38400); //use for bluetooth
  Serial.begin(38400); // for logging
}
void loop() {
 // Default value - no movement when the Joystick stays in the center
  x = 510 / 4;
  y = 510 / 4;
  // Read the incoming data from the Joystick, or the master Bluetooth device

  while (BTSerial.available() >= 2) {
    x = BTSerial.read();
    //testing: remove serial.print bbefore deplozment for performance!
    Serial.print("x: ");
    Serial.println(x);
    delay(10);
    y = BTSerial.read();
    Serial.print("y: ");
    Serial.println(y);
  }

  delay(10);
  
  // Convert back the 0 - 255 range to 0 - 1023, suitable for motor control code below
  xAxis = x*4;
  yAxis = y*4;
  // Y-axis used for forward and backward control
  if (yAxis < 470) {
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if (yAxis > 550) {
    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }
  // X-axis used for left and right control
  if (xAxis < 470) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
  if (xAxis > 550) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. Motors start moving at around 40 PWM signal. Adjustet this to motors for sumobot competition!
  if (motorSpeedA < 40) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 40) {
    motorSpeedB = 0;
  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

  
}
