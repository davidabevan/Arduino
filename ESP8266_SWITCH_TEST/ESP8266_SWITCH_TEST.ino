int switchPin = 0;
int LedPin = 16;
int switchValue;

void setup() { 
  pinMode(LedPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  // Read the switch value
  switchValue = digitalRead(switchPin);
  /* Set the LED output pin the opposit of what is read on the switch
   * input pin  
   */
  digitalWrite(LedPin, !switchValue); 
   
}
