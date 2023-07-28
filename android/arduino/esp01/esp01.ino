#include <ESP8266WiFi.h>

const char* ssid = "Dumbledore's IT Staff";
const char* password = "password";
const int port = 80;

WiFiServer server(port);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.begin(); 
  Serial.println("TCP server started");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");

    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\n');
        Serial.println(request);

      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}
