const int PIR_PIN = 2;     // PIR Sensor Signal Pin
const int LED_PIN = 13;    // LED Pin
const int BUZZER_PIN = 8;  // Buzzer Pin

int pirState = LOW;        // Initial state: no motion
int val = 0;               // Variable for reading sensor status

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_PIN, INPUT);      // Set PIR pin as Input
  pinMode(LED_PIN, OUTPUT);     // Set LED pin as Output
  pinMode(BUZZER_PIN, OUTPUT);  // Set Buzzer pin as Output
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(PIR_PIN);  // Read PIR sensor value
  Serial.println(val);
  if (val == HIGH) { 
    Serial.println("!!!! motion detected");
    // Motion detected: Turn on LED and sound the buzzer
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);    // Play a 1000 Hz tone on the buzzer
    
    if (pirState == LOW) {
      Serial.println("ALARM: Motion detected!");
      pirState = HIGH;
    }
  } else { 
    Serial.println("!!!! motion NOT detected");
    // No motion: Turn off LED and stop the buzzer
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);        // Silence the buzzer
    
    if (pirState == HIGH) {
      Serial.println("System clear: Motion ended.");
      pirState = LOW;
    }
  }
  delay(100);
}
