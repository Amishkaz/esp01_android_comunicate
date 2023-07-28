String name = "";  
String Mobile = "";  
String Address = "";  
String Email = "";  
  
void setup()   
{  
    Serial.begin(115200);  
}  
  
void loop()   
{  
    Serial.println("Enter your name.");  
    while (Serial.available() == 0)   
    { //Wait for user input  }  
    name = Serial.readString(); //Reading the Input string from Serial port.  
    Serial.println("YOUR NAME:" + name);  
    Serial.println("");  
    while (Serial.available() == 0) {}  
    }
} 
