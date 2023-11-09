#include <dht11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int RELAY1 = 12;
const int RELAY2 = 11;
const int RELAY3 = 10;
const int soilPin = A0;
unsigned long buttonTime = 0;
const int buttonPin = 2;
const int dhtPin = 5; // DHT11 sensor pin
dht11 DHT; // Create an instance of the DHT11 library
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool displayState = false;
unsigned long displayStartTime = 0;

float soilPercentage = 0.0; // Initialize soil moisture
float temperature = 0.0;    // Initialize temperature
float humidity = 0.0;       // Initialize humidity

void setup() {
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  lcd.init();
  lcd.noBacklight();
  attachInterrupt(digitalPinToInterrupt(buttonPin), ButtonPressed, FALLING);
  Serial.begin(9600);
}

void loop() {
  int soilValue;

  soilValue = analogRead(soilPin);
  soilPercentage = 100.0 - ((soilValue / 1023.0) * 100.0);

  int chk = DHT.read(dhtPin);
  temperature = DHT.temperature;
  humidity = DHT.humidity;

  Serial.print("Soil Moisture = ");
  Serial.print(soilPercentage);
  Serial.println("%");

  Serial.print("Temperature = ");
  Serial.println(temperature);

  Serial.print("Humidity % = ");
  Serial.println(humidity);

  if (soilValue > 40) {
    digitalWrite(RELAY1, HIGH);
  } else {
    digitalWrite(RELAY1, LOW);
  }
  delay(1000);

  if (temperature > 20) {
    digitalWrite(RELAY2, HIGH);
  } else {
    digitalWrite(RELAY2, LOW);
  }
  delay(1000);

  if (humidity > 40) {
    digitalWrite(RELAY3, HIGH);
  } else {
    digitalWrite(RELAY3, LOW);
  }
  delay(1000);

  if (displayState & (millis() - displayStartTime >= 5000)) {
    TurnOffDisplay();
    displayState = false;
  }
}

void TurnOnDisplay() {
  lcd.setCursor(1, 0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print("^");

  lcd.setCursor(10, 0);
  lcd.print("H");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(2, 1);
  lcd.print("SM:");
  lcd.print(soilPercentage);
}

void TurnOffDisplay() {
  lcd.clear();
  lcd.noBacklight();
}

void ButtonPressed() {
  buttonTime = millis();
  displayStartTime = millis();
  displayState = true;
  TurnOnDisplay(); // Turn on the display when the button is pressed
}
