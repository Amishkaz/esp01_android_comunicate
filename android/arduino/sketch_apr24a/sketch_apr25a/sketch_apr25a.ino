#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200);
  
}

void loop() {
 String data="<h1>test<h1>";
 mySerial.print(data+"\n");
 delay(1000);
 
}
