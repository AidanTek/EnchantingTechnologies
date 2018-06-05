/* 
Ultrasonic range sensor and vibration driver tutorial. The range sensor needs to be supplied with 5V and requires any 2 digital
pins to function. The vibration driver is designed to run at 3V and will consume 60mA at this voltage, when running at 5V, place a 
100ohm resistor in series.

Example by Aidan Taylor. Fab-Cre8 Enchanting Technologies. 2018.
*/


const uint8_t echoPin = 7; // Echo Pin
const uint8_t trigPin = 4; // Trigger Pin
const uint8_t vibPin = 11; // Vibration Driver

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(vibPin, OUTPUT);
}

void loop() {
 uint16_t vibIntensity;

 uint32_t duration, distance; // memory used to store/calculate distance
 
 digitalWrite(trigPin, LOW); // reset the trigPin just in case
 delay(2); 

 digitalWrite(trigPin, HIGH); 
 delay(10); 
 digitalWrite(trigPin, LOW); // send a 10ms pulse
 
 duration = pulseIn(echoPin, HIGH); // pulseIn measures time in µseconds
                                    
 distance = (duration/58.2); // rough conversion to cm 
 
 if (distance < 2 || distance > 100) { // pulseIn will return 0 if no object is in range
  Serial.println("out of range");
  digitalWrite(vibPin, LOW); 
 }
 else {
  Serial.print("Object: ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("Raw data = ");
  Serial.println(duration);
  vibIntensity = map(distance, 100, 2, 10, 255);
  analogWrite(vibPin, vibIntensity);
 }
 
 //Delay 50ms before next reading.
 delay(50);
}
