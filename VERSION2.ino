#define soilMoist 7
#define sensorPin A0
const int RELAY_PIN = 12;

int readSensor() { // Corrected the function declaration
  digitalWrite(RELAY_PIN, HIGH);
  delay(1000);
  digitalWrite(RELAY_PIN, LOW);
  delay(1000);

  digitalWrite(soilMoist, HIGH);
  delay(10);
  int val = analogRead(sensorPin);
  digitalWrite(soilMoist, LOW);
  return val;
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(sensorPin, INPUT); // Corrected pinMode for sensor
  Serial.begin(9600);
}

void loop() {
 int sensorValue = readSensor(); // Read the soil moisture sensor

  Serial.print("Analog output: ");
  Serial.println(sensorValue);

  if (sensorValue < 1020 ) { // Adjust the threshold value as needed
    digitalWrite(RELAY_PIN, LOW); // Turn on the relay
  }
   else 
    digitalWrite(RELAY_PIN, HIGH); // Turn off the relay
  

  delay(1000);
}

