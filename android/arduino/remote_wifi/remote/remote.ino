#include <IRremote.h>
//Define Pins
int io0 = 2;
int io2 = 3;
int fan=5;
int light=4;
int RECV_PIN = 11;
//IR Library stuff
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(fan, OUTPUT);
  pinMode(light, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(io0), lightControl, CHANGE);
  attachInterrupt(digitalPinToInterrupt(io2), fanControl, CHANGE);
  //Enable serial usage and IR signal in
  //Serial.begin(9600);
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {//irrecv.decode(&results) returns true if anything is recieved, and stores info in varible results
    unsigned int value = results.value; //Get the value of results as an unsigned int, so we can use switch case
    //Serial.println(value);
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
      
    }
    
    
    irrecv.resume(); // Receive the next value
  }
  
}
void lightControl(){
  if(digitalRead(io0)==1){
  digitalWrite(light,HIGH);
  }else if(digitalRead(io0)==0){
  digitalWrite(light,LOW);
  }
}
void fanControl(){
  if(digitalRead(io2)==1){
  digitalWrite(fan,HIGH);
  }else if(digitalRead(io2)==0){
  digitalWrite(fan,LOW);
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
