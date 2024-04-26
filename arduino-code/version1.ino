/*

*/

#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  4

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266

//int variable = 777;
float humidity, temp_f;  // Values read from sensor

void setup() {
  Serial.begin(9600);
  dht.begin();           // initialize temperature sensor
}

void loop() {
  //Serial.println(variable);

  humidity = dht.readHumidity();          // Read humidity (percent)
  temp_f = dht.readTemperature(true);     // Read temperature as Fahrenheit

  Serial.println(humidity);
  
  delay(100);
}
