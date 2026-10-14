const int sensorPin = A0;
const float baselineTemp = 28.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(sensorPin);
  Serial.println("sensor Value: ");
  Serial.println(sensorVal);
  //convert to voltage
  float voltageTempSensor = (sensorVal/1024.0)*5.0;
  Serial.println("Volts: ");
  Serial.println(voltageTempSensor);

  Serial.println("Degree C: ");
  float temperature = (voltageTempSensor-0.5)*100;
  Serial.println(temperature);

  if(temperature < baselineTemp+2){
    Serial.println("1111111!!!!!!");
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }else if(temperature >= baselineTemp+2 && temperature < baselineTemp+6){
    Serial.println("2222222!!!!!!");
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);    
  }else if(temperature >= baselineTemp+6){
    Serial.println("3333333!!!!!");
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);    
  }
  delay(1000);
}
