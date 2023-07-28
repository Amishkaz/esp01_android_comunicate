
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Dumbledore's IT Staff"
#define STAPSK  "password"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "13.127.1.70";
const uint16_t port = 8080;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
 
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

}

void loop() {
  
  // This will send a string to the server
  Serial.println("Enter data:");
  while (Serial.available() == 0) {
    // Wait for user input
  }
  String data = Serial.readStringUntil('\n'); // Read user input until newline character
  
  Serial.println("Sending data to server: " + data);
  if (client.connected()) {
    client.println(data); // Send user input to server
  }else if (client.connect(host, port)) {
    client.println(data);
  }else{
    Serial.println("error");
      
  }
    digitalWrite(LED_BUILTIN, HIGH);
}
