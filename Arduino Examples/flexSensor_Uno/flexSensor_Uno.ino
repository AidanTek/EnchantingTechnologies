
byte flexPin = A0;
int flexValue = 0;

byte ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  flexValue = analogRead(flexPin);
  Serial.println(flexValue);

  if(flexValue < 150) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(100);
}
