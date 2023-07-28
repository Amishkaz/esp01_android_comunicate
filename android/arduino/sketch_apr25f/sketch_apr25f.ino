String ssid     = "Dumbledore's IT Staff";  // SSID to connect to
String password = "12345678"; // Our virtual wifi has no password (so dont do your banking stuff on this network)


void setup() {
  Serial.begin(115200);
  Serial.write("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        // Wait a little for the ESP to respond
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
