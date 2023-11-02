#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#define sensorPower 7 

const int RELAY1 = 12;
const int RELAY2 = 11;
const int RELAY3 = 10;
const int soilPin = A0;
const int buttonPin = 2;
const int dhtPin = 5;
dht11 DHT;

int soilValue;        //intitailising 
int temperature;
int humidity;
int soilPercentage;

volatile byte state = LOW;
unsigned long buttonOnTime = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Set up button pin as an input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize the LCD and turn off the backlight
  lcd.init();
  lcd.noBacklight();

  // Set relay pins as outputs
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);

  // Attach an interrupt to the buttonPin that triggers the LCD function on CHANGE
  attachInterrupt(digitalPinToInterrupt(buttonPin), LCD, CHANGE);

  // Initialize the serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read soil moisture value from the analog pin
  soilValue = analogRead(soilPin);
  // Calculate soil moisture percentage
  soilPercentage = 100 - ((soilValue / 1023) * 100);

  // Read temperature and humidity from the DHT11 sensor
  int chk = DHT.read(dhtPin);
  temperature = DHT.temperature;
  humidity = DHT.humidity;

  // Print soil moisture, temperature, and humidity to the serial monitor
  Serial.print("Soil Moisture = ");
  Serial.print(soilValue);
  Serial.println("%");
  delay(500);

  Serial.print("Temperature = ");
  Serial.println(temperature);
  delay(500);

  Serial.print("Humidity % = ");
  Serial.println(humidity);
  delay(500);

  // Control relays based on sensor readings
  if (soilValue > 13) {
    digitalWrite(RELAY1, HIGH);
  } else {
    digitalWrite(RELAY1, LOW);
  }

  if (temperature > 23) {
    digitalWrite(RELAY2, HIGH);
  } else {
    digitalWrite(RELAY2, LOW);
  }

  if (humidity > 66) {
    digitalWrite(RELAY3, HIGH);
  } else {
    digitalWrite(RELAY3, LOW);
  }

  // If the button is pressed, turn on the LCD and display sensor values for 5 seconds
  if (millis() - buttonOnTime <= 5000) {
    screenOn();
    TurnOnDisplay();
  } else {
    TurnOffDisplay();
  }
}

// Turn off the LCD backlight and clear the display
void TurnOffDisplay() {
  lcd.clear();
  lcd.noBacklight();
}

// Turn on the LCD backlight and display temperature, humidity, and soil moisture
void TurnOnDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.setCursor(10, 0);
  lcd.print("H:");
  lcd.print(humidity);
  lcd.setCursor(1, 1);
  lcd.print("SM:");
  lcd.print(soilValue);
}

// Turn on the LCD backlight and display
void screenOn() {
  lcd.display();
  lcd.backlight();
}

// Function called when the button is pressed to record the button press time
void LCD() {
  buttonOnTime = millis();
}


