#include <ESP8266WiFi.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* server_address = "192.168.0.100"; // replace with your server IP address
const int server_port = 12345; // replace with your server port number

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  if (!client.connected()) {
    if (!client.connect(server_address, server_port)) {
      Serial.println("Connection failed");
      return;
    }
    Serial.println("Connected to server");
  }
  client.write("Hello, server!");
  delay(1000);
}
