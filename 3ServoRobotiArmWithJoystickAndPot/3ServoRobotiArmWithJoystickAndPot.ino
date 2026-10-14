#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// --- Pin and Channel Definitions ---
const int potElbowPin = A0;         // Potentiometer controls the elbow
const int joystickXPin = A1;        // Joystick X-axis controls the wrist
const int joystickYPin = A2;        // Joystick Y-axis controls the gripper

const int ELBOW_CHANNEL = 0;       // Elbow is on channel 0
const int WRIST_CHANNEL = 4;       // Wrist is on channel 4
const int GRIPPER_CHANNEL = 15;    // Grabber is on channel 15

// --- Angle Limits ---
const int WRIST_MIN_ANGLE = 0;      
const int WRIST_MAX_ANGLE = 20;    

const int GRIPPER_MIN_ANGLE = 0;    
const int GRIPPER_MAX_ANGLE = 180;   

#define SERVOMIN  100 
#define SERVOMAX  600 

// --- Filtering & Deadzones ---
const int POT_DEADZONE = 5;          
const int JOYSTICK_DEADZONE = 25;    

// Smoothing variable for the potentiometer (Low-pass filter)
float smoothedElbowVal = 0;
const float SMOOTHING_FACTOR = 0.15; // Lower = smoother/less jitter (0.05 to 0.3)

int lastElbowVal = 0;
int lastWristVal = 0;
int lastGripperVal = 0;

void setup() {
  Serial.begin(9600);
  delay(1000); 
  pwm.begin();
  pwm.setPWMFreq(60); 

  // Initialize smoothing baseline with actual pin reading
  smoothedElbowVal = analogRead(potElbowPin);
  lastElbowVal = (int)smoothedElbowVal;
  lastWristVal = analogRead(joystickXPin);
  lastGripperVal = analogRead(joystickYPin);

  // Safe starting position
  pwm.setPWM(ELBOW_CHANNEL, 0, 325);
}

void loop() {
  // --- Advanced Potentiometer Filtering ---
  int rawElbowVal = analogRead(potElbowPin);
  
  // Apply Exponential Moving Average filter to kill electrical noise
  smoothedElbowVal = (SMOOTHING_FACTOR * rawElbowVal) + ((1.0 - SMOOTHING_FACTOR) * smoothedElbowVal);
  int elbowVal = (int)smoothedElbowVal;

  int wristVal = analogRead(joystickXPin);
  int gripperVal = analogRead(joystickYPin);

  // Calculate current angles
  int elbowAngle = map(elbowVal, 0, 1023, 120, 75);
  int wristAngle = map(wristVal, 0, 1023, WRIST_MIN_ANGLE, WRIST_MAX_ANGLE);
  
  // Reversed gripper direction by swapping MIN and MAX angles
  int gripperAngle = map(gripperVal, 0, 1023, GRIPPER_MAX_ANGLE, GRIPPER_MIN_ANGLE);

  bool updated = false;

  // --- Elbow (Filtered Potentiometer) ---
  if (abs(elbowVal - lastElbowVal) > POT_DEADZONE) {
    lastElbowVal = elbowVal;
    int elbowPulse = map(elbowAngle, 75, 120, 275, 375);
    pwm.setPWM(ELBOW_CHANNEL, 0, elbowPulse);
    updated = true;
  }

  // --- Wrist (Joystick X-axis) ---
  if (abs(wristVal - lastWristVal) > JOYSTICK_DEADZONE) {
    lastWristVal = wristVal;
    int wristPulse = map(wristAngle, WRIST_MIN_ANGLE, WRIST_MAX_ANGLE, SERVOMIN, SERVOMAX);
    pwm.setPWM(WRIST_CHANNEL, 0, wristPulse);
    updated = true;
  }

  // --- Gripper (Joystick Y-axis) ---
  if (abs(gripperVal - lastGripperVal) > JOYSTICK_DEADZONE) {
    lastGripperVal = gripperVal;
    int gripperPulse = map(gripperAngle, GRIPPER_MIN_ANGLE, GRIPPER_MAX_ANGLE, SERVOMIN, SERVOMAX);
    pwm.setPWM(GRIPPER_CHANNEL, 0, gripperPulse);
    updated = true;
  }

  if (updated) {
    Serial.print("Elbow: ");
    Serial.print(elbowAngle);
    Serial.print("° | Wrist: ");
    Serial.print(wristAngle);
    Serial.print("° | Gripper: ");
    Serial.print(gripperAngle);
    Serial.println("°");
  }

  delay(15);
}