const int interruptPin = 2;  // Pin for the software interrupt

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);  // Set the interrupt pin as input with internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, CHANGE);  // Attach interrupt to the pin
  Serial.begin(9600);  // Initialize the serial communication
}

void loop() {
  if (Serial.available()) {  // Check if there is serial input
    char input = Serial.read();  // Read the input character
    Serial.print(input);  // Echo the input back to the serial monitor
  }
}

void handleInterrupt() {
  // This function is called when the interrupt is triggered
  Serial.println("Software Interrupt Triggered!");
}
