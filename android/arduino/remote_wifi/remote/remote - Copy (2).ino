#include <IRremote.h>
#include <Servo.h>
Servo servoBase;
//Define Pins
int fan=3;
int light=4;
int RECV_PIN = 11;
//IR Library stuff
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{
  servoBase.attach(A1);//Pin a utilizar para servo
  servoBase.write(0);
  //Set Led Pins
  pinMode(fan, OUTPUT);
  pinMode(light, OUTPUT);
  
  //Enable serial usage and IR signal in
  Serial.begin(9600);
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {//irrecv.decode(&results) returns true if anything is recieved, and stores info in varible results
    unsigned int value = results.value; //Get the value of results as an unsigned int, so we can use switch case
    Serial.println(value);
    switch (value) {
      case 53242: 
        digitalWrite(fan, HIGH);
        break;
      
      case 53196: 
        digitalWrite(fan, LOW);
        break;
      
      case 53190:
        digitalWrite(light, HIGH);
        break;
      
      case 53218:
        digitalWrite(light, LOW);
        break;
      
      case 53238:
        digitalWrite(light, HIGH);
        digitalWrite(fan, HIGH);
        break;
      
      case 53247:
        servoBase.write(0);
        delay(2000);
        break;
      
      case 53194:
        servoBase.write(30);
        delay(2000);
        break;
      case 53230:
        servoBase.write(60);
        delay(2000);
        break;
      case 53201:
        servoBase.write(120);
        delay(2000);
        break;
      
    }
    
    
    irrecv.resume(); // Receive the next value
  }
}
/* 
My remote             tinkercad
53218 power light off 255
53196 tray fan off    16575
53238 enter all on    41055
53194 1 30            2295
53230 2 60            34935
53201 3 120           18615
53247 4 0             12495
53223 tools 
53244 info
53242 up fan on       20655
53190 down light on   4335
*/
