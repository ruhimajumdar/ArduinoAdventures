#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 7     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // Change to DHT22 if you are using a DHT22 sensor

DHT dht(DHTPIN, DHTTYPE);

// Initialize LiquidCrystal with your exact parallel wiring pin map:
// (RS, Enable, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  
  // Initial splash screen
  lcd.setCursor(0, 0);
  lcd.print("Env Monitor Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(2000); // Wait 2 seconds between measurements

  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature in Celsius

  // Check if readings failed and exit early to try again
  if (isnan(h) || isnan(t)) {
    Serial.println("Error reading from DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    return;
  }

  // Print diagnostics to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  |  Temperature: ");
  Serial.print(t);
  Serial.println("°C");

  // Print readings to the LCD Screen
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223); // Degree symbol
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%   ");
}