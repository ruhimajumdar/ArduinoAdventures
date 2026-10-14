#include <DHT.h>

#define DHTPIN 7     
#define DHTTYPE DHT11   // Change to DHT22 if using a white or different sensor model
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT Sensor Diagnostic Test");
  dht.begin();
}

void loop() {
  delay(2000);

  // Read humidity and temperature values
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius
  float f = dht.readTemperature(true); // Fahrenheit

  // Check if any reads failed
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error: Failed to read from DHT sensor!");
    return;
  }

  // Print results to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  |  ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C (");
  Serial.print(f);
  Serial.println("°F)");
}