
int switchState = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);//.switch
  pinMode(3, OUTPUT);//green
  pinMode(4, OUTPUT);//yellow
  pinMode(5, OUTPUT);//red
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(2);

  if (switchState == LOW){
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);//red
  }
  else {
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);//yellow
    digitalWrite(5, LOW);
    delay(250);
    digitalWrite(3, HIGH);//green
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(250);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);//red
    delay(250);
  }

}//back to the beginning of the loop
