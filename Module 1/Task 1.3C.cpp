/*
Multiple Inputs with Interrupts
*/

// Input pins
const uint8_t button = 2;
const uint8_t ptr = 3;

// LED output pins
const uint8_t led1 = 8;
const uint8_t led2 = 12;

//	LED intital status
uint8_t led1Status = LOW;
uint8_t led2Status = HIGH;

void setup()
{
  // Pin initialisation
  pinMode(ptr, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);  
  
  // Serial port initialisation (with baudrate)
  Serial.begin(9600);
  
  // Interrupt calls
  attachInterrupt(digitalPinToInterrupt(ptr), ptrToggle, CHANGE);
  attachInterrupt(digitalPinToInterrupt(button), buttonToggle, FALLING);
  
  // Serial monitor legend
  Serial.println("LED Status Legend:");
  Serial.println("If == 1: LED is on");
  Serial.println("If == 0: LED is off");
  Serial.println();
  
  // Setting LED 2 to its initial status (HIGH/on)
  digitalWrite(led2, led2Status);
}

void loop()
{
  delay(1000); // Delay a little bit to improve simulation performance
}

// Method called when the button pin (digital pin 2) is interrupted
// The interrupt will be caused by the button's voltage falling (from 1 to 0)
// Changes the status of LED1
void buttonToggle()
{
  led1Status = !led1Status;
  digitalWrite(led1, led1Status);
  Serial.print("LED #1 Status: ");
  Serial.println(led1Status);
  Serial.println();
}

// Method called when the ptr pin (digital pin 3) is interrupted
// The interrupt will be caused by the light intensity changing from low to high and vice versa
// Changes the status of LED 1
void ptrToggle()
{
  led2Status = !led2Status;
  digitalWrite(led2, led2Status);
  Serial.print("LED #2 Status: ");
  Serial.println(led2Status);
  Serial.println();
}
