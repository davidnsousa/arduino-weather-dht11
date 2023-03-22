#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 21 
#define DHTTYPE DHT11   

DHT_Unified dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);

uint32_t delayMS;

void setup() {
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  lcd.init();
  lcd.backlight();
}

void loop() {
  
  // Delay between measurements.
  delay(delayMS);
  lcd.clear();

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  // Set cursor to row 1 and print the temperature
  lcd.setCursor(0,0);
  lcd.print("Temperatura: ");
  int temperature = (int) event.temperature; 
  String T = String(temperature) + "C";
  lcd.print(T);

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);

  // Set cursor to row 2 and print the temperature
  lcd.setCursor(0,1);
  lcd.print("Humidade:    ");
  int humidity = (int) event.relative_humidity;
  String H = String(humidity) + "%";
  lcd.print(H);

}
