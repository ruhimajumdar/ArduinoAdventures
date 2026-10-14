#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// --- Pin and Channel Definitions ---
const int potElbowPin = A0;         // Potentiometer 1 controls the elbow
const int potWristGripperPin = A1;  // Potentiometer 2 controls wrist & gripper

const int ELBOW_CHANNEL = 13;       // Elbow is on channel 13
const int WRIST_CHANNEL = 14;       // Wrist is on channel 14
const int GRIPPER_CHANNEL = 15;     // Grabber is on channel 15

// --- Servo Angle Limits (in degrees) ---
const int ELBOW_MIN_ANGLE = 0;
const int ELBOW_MAX_ANGLE = 160;

const int WRIST_MIN_ANGLE = 20;
const int WRIST_MAX_ANGLE = 160;

const int GRIPPER_MIN_ANGLE = 10;   // Fully closed
const int GRIPPER_MAX_ANGLE = 90;   // Fully open

// Standard pulse length min/max for typical servos (0° to 180°)
#define SERVOMIN  150 
#define SERVOMAX  600 

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60Hz
}

void loop() {
  // 1. Read the potentiometers (0 to 1023)
  int elbowVal = analogRead(potElbowPin);
  int actionVal = analogRead(potWristGripperPin);

  // 2. Map potentiometer values to target angles
  int elbowAngle = map(elbowVal, 0, 1023, ELBOW_MIN_ANGLE, ELBOW_MAX_ANGLE);
  int wristAngle = map(actionVal, 0, 1023, WRIST_MIN_ANGLE, WRIST_MAX_ANGLE);
  int gripperAngle = map(actionVal, 0, 1023, GRIPPER_MIN_ANGLE, GRIPPER_MAX_ANGLE);

  // 3. Convert target angles into PCA9685 pulse lengths
  int elbowPulse = map(elbowAngle, 0, 180, SERVOMIN, SERVOMAX);
  int wristPulse = map(wristAngle, 0, 180, SERVOMIN, SERVOMAX);
  int gripperPulse = map(gripperAngle, 0, 180, SERVOMIN, SERVOMAX);

  // 4. Send signals to the correct PCA9685 channels
  pwm.setPWM(ELBOW_CHANNEL, 0, elbowPulse);
  pwm.setPWM(WRIST_CHANNEL, 0, wristPulse);
  pwm.setPWM(GRIPPER_CHANNEL, 0, gripperPulse);

  delay(15); // Small delay for stable movement
}