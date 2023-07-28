#include <SoftwareSerial.h>
#define TIMEOUT 5000 // mS
#define LED 5
SoftwareSerial mySerial(7, 6); // RX, TX
const int button = 11;
int button_state = 0;
void setup()
{
pinMode(LED_BUILTIN, OUTPUT);
 pinMode(LED,OUTPUT);
 pinMode(button,INPUT); 
 Serial.begin(115200);
 mySerial.begin(115200);
 SendCommand("AT+RST", "Ready");
 delay(5000);
 SendCommand("AT+CWMODE=1","OK");
 SendCommand("AT+CIFSR", "OK");
 SendCommand("AT+CIPMUX=1","OK");
 SendCommand("AT+CIPSERVER=1,80","OK");
}
void loop(){
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 
}
