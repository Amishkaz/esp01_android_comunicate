#include <ESP8266WiFi.h>

const char* ssid = "Dumbledore's IT Staff";
const char* password = "password";
//const char* ssid = "The Promised LAN";
//const char* password = "noWIFI4U";
const int port = 80;

WiFiServer server(port);

void setup() {
  
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    Serial.println("Connecting to WiFi...");
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
  blink(3);
  digitalWrite(LED_BUILTIN, HIGH);
  server.begin();
  Serial.println("TCP server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  //digitalWrite(LED_BUILTIN, HIGH);
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");

    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\n');
        Serial.println(request);
        //blink(5);
        client.println(action(request));
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

String action(String command){
  if(command=="fanOn")
  {
    Serial.println("fan on");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(0, LOW);
    return "fan on";
  }else if (command=="fanOff")
  {
    Serial.println("fan off");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(0, HIGH);
    return "fan off";  
  }else if (command=="lightOn")
  {
    Serial.println("light off");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(2, HIGH);
    return "light off";
  }else if (command=="lightOff")
  {
    Serial.println("light on");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(2, LOW);
    return "light on";  
  }else if (command=="blueoff")
  {
    Serial.println("Blue off");
    digitalWrite(LED_BUILTIN, HIGH);
    return "blue off";  
  }else{
  return "no condition";
  }
}

void blink(int x){
  for(int i=0;i<x;i++){
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    
  }  
}
