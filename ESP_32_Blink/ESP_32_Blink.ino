
int LED_BUILTIN = 2;

void setup() {
pinMode (LED_BUILTIN, OUTPUT);

}

void loop() {
digitalWrite(LED_BUILTIN, HIGH);
delay(500);
digitalWrite(LED_BUILTIN, LOW);
delay(1000);
}
