#define LED_ON HIGH
#define LED_OFF LOW

int ledPin;

void LedInit(int LED_PIN)
{
  pinMode(LED_PIN, OUTPUT);
  ledPin = LED_PIN;
}

void WriteLed(char c, FILE* file)
{
  if (c == '1')
  {
    digitalWrite(ledPin, LED_ON);
  }
  else if (c == '0')
  {
    digitalWrite(ledPin, LED_OFF);
  }
  
  return c;
}
