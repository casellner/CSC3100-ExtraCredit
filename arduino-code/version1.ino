/*

*/

#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  4

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266

int lightPin = 13;
String mode = "0";
float humidity, temp_f;  // Values read from sensor

void setup() {
  pinMode(lightPin, OUTPUT);
  Serial.begin(9600);
  dht.begin();           // initialize temperature sensor
}

void loop() {
  if(Serial.available() > 0) {
    while(Serial.available() > 0) {
      mode = char(Serial.read());
    }
  }

  if (mode == "0") {
    digitalWrite(lightPin, LOW);
  }
  else if (mode == "1") {
    digitalWrite(lightPin, HIGH);
  }

  temp_f = dht.readTemperature(true);     // Read temperature as Fahrenheit
  humidity = dht.readHumidity();          // Read humidity (percent)
  Serial.print("Temperature: ");
  Serial.print(temp_f);
  Serial.print("   Humidity: ");
  Serial.println(humidity);
    
  delay(100);
}
