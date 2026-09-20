int cLED = 13;

void setup()
{
 	pinMode(cLED, OUTPUT);
}

void loop()
{  digitalWrite(cLED, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(cLED, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
