#define sensorPower 7 
#define sensorPin A0

void setup() {
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
}

void loop() {

  Serial.print("Analog output: ");
  Serial.println(readSensor());

  delay(1000);
}

int readSensor() {
  digitalWrite(sensorPower, HIGH);  
  delay(10);                        
  int val = analogRead(sensorPin);  
  digitalWrite(sensorPower, LOW);   
  return val;                       
}
