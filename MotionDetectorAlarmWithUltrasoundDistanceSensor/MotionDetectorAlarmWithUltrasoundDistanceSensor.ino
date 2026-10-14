// Pin Definitions
const int TRIG_PIN   = 3;   // Ultrasonic Trigger Pin
const int ECHO_PIN   = 4;   // Ultrasonic Echo Pin
const int LED_PIN    = 13;  // Alarm LED Pin
const int BUZZER_PIN = 8;   // Alarm Buzzer Pin

// Threshold distance to trigger the alarm (in centimeters)
const int DISTANCE_THRESHOLD = 10; 

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond HIGH pulse to send out the ultrasonic wave
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the returning pulse in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in centimeters (speed of sound is ~0.034 cm/us)
  int distance = duration * 0.034 / 2;

  // Print distance to Serial Monitor for real-time debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Alarm condition: Trigger if an object is within threshold (and valid range)
  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    Serial.println("!!!!! Object detected");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // 1000 Hz alarm tone
  } else {
    Serial.println("nothing detected");
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);     // Turn off sound when clear
  }

  delay(100); // Short delay before next sample
}