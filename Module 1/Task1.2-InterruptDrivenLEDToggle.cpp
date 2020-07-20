/*
  Interrupt Driven Light Toggle
*/
//	Pin Variables
const uint8_t button = 3; // Pin 3 maps to int1 on the Arduino Board
const uint8_t led = 10;

// 	Global Variables
uint8_t ledStatus = LOW;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  // Interrupt initialised in the setup function, will look for when the button state falls
  attachInterrupt(digitalPinToInterrupt(button), buttonToggle, FALLING);
  Serial.println("LED Status Legend:");
  Serial.println("If == 1: LED is on");
  Serial.println("If == 0: LED is off");
  Serial.println();
}

void loop()
{
//	No need for any action in the loop, delay just to give the processor time
  delay(1000);
}

//	buttonToggle method will flip the LED's status when the interrupt is triggered.
void buttonToggle()
{
  ledStatus = !ledStatus;
  digitalWrite(led, ledStatus);
  Serial.print("LED Status: ");
  Serial.println(ledStatus);
  Serial.println();
}
