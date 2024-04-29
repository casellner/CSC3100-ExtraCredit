#include <ESP8266WiFi.h> 

const char* ssid = "EagleNet"; 
const char* password = "VAA39x4H";
const int serverPort = 80; 

WiFiClient client;

int motionSensorPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(motionSensorPin, INPUT);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  int motionState = digitalRead(motionSensorPin);

  if (motionState == HIGH) {
    Serial.println("Motion Detected");
    sendDataToServer("Motion Detected");
  } else {
    Serial.println("Motion Stopped");
    sendDataToServer("Motion Stopped");
  }

  delay(1000);
}

void sendDataToServer(String message) {
  if (client.connect(serverAddress, serverPort)) {
    Serial.println("Connected to server");

    client.print("POST /endpoint HTTP/1.1\r\n"); // Adjust endpoint as needed
    client.print("Host: ");
    client.print(serverAddress);
    client.print("\r\n");
    client.print("Content-Type: application/x-www-form-urlencoded\r\n");
    client.print("Content-Length: ");
    client.print(message.length());
    client.print("\r\n\r\n");
    client.print(message);

    Serial.println("Data sent to server");

    delay(100); // Wait for server response (adjust as needed)
    client.stop();
  } else {
    Serial.println("Failed to connect to server");
  }
}
