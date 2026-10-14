#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
// (RS, Enable, D4, D5, D6, D7) matching your wiring
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a test message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("LCD TEST: OK");
  
  Serial.println("System Initialized. LCD and Serial are active.");
}

void loop() {
  int seconds = millis() / 1000;
  
  // Print uptime to Serial Monitor
  Serial.print("Uptime: ");
  Serial.print(seconds);
  Serial.println(" seconds");

  // Print uptime to LCD screen row 1
  lcd.setCursor(0, 1);
  lcd.print("Uptime: ");
  lcd.print(seconds);
  lcd.print("s   ");
  
  delay(1000);
}