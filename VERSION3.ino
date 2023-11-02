const int RELAY1 = 12;
const int RELAY2 = 11;
const int RELAY3 = 10;
const int soil = 0;

#include <dht11.h>
#define DHT11Pin 5
dht11 DHT11;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  int soil;
  float soil_percentage;  //making the Soilmoisture values display in percentages
  soil = analogRead(soil);
  soil_percentage = (100 - ((soil / 1023.00) * 100));
  int chk = DHT11.read(DHT11Pin);
  Serial.print("SoilMoisture = ");
  Serial.println(soil_percentage);  // displaying the values of the soilmoisture sensor
  Serial.print("%");

  Serial.print("Temperature = ");  // displaying the temperature values of the Dht11 sensor
  Serial.println(DHT11.temperature);

  Serial.print("Humidity % = ");  // displaying the Humidty values of the s DHT11 sensor
  Serial.println(DHT11.humidity);

  if (soil > 600) {  // Turning on relay 1 based on the values from the soilmoisture sensor (waterpump)
    digitalWrite(RELAY1, HIGH);
  }

  else
    digitalWrite(RELAY1, LOW);
  delay(1000);

  if (DHT11.temperature > 40) {  //Turning on relay2 based on the temperature values from the Dht11 sensor (fan)
    digitalWrite(RELAY2, HIGH);
  }

  else
    digitalWrite(RELAY2, LOW);
  delay(1000);

  if (DHT11.humidity > 30) {  //Turning on relay3 based on the humidty values from the Dht11 sensor (fan)
    digitalWrite(RELAY3, HIGH);
  }

  else (digitalWrite(RELAY3, LOW));
  delay(1000);

  lcd.setCursor(1, 0);  //Set cursor to character 1 on line 0
  lcd.print("Temp:");
  lcd.print(DHT11.temperature);
  lcd.print("^");

  lcd.setCursor(10, 0);  //Set cursor to character 10 on line 0
  lcd.print("H");
  lcd.print(DHT11.humidity);
  lcd.print("%");
  lcd.setCursor(2, 1);  //Set cursor to character 2 on line 1
  lcd.print("SM:");
  lcd.print(soil_percentage);
}
