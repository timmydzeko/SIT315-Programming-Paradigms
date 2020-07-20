/*
  Automatic Dusk Detecting Light
*/

int lightReading = 0;

int inverseReading = 0;

int adjustedInvRead = 0;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);

  pinMode(3, OUTPUT);
}

void loop()
{
  // Photoresistor will read in light values
  lightReading = analogRead(A0);
  Serial.print("Brightness level: ");
  Serial.println(lightReading);
  Serial.println("");
  delay(2); // Wait for 2 millisecond(s)
  // Maximum reading for light intensity at time of
  // recording was 169.
  // The inverse is used to fade out light as the
  // brightness measured by the photoresistor
  // increases.
  inverseReading = (169 - lightReading);
  delay(2); // Wait for 2 millisecond(s)
  adjustedInvRead = map(inverseReading, 0, 1023, 0, 255);
  analogWrite(3, adjustedInvRead);
  Serial.print("Light level set: ");
  Serial.println(adjustedInvRead);
  Serial.println("");
  delay(10); // Wait for 10 millisecond(s)
}
