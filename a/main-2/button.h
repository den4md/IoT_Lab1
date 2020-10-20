#define BUTTON_ON LOW
#define BUTTON_OFF HIGH

int buttonPin;

void ButtonInit(int BUTTON_PIN)
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  buttonPin = BUTTON_PIN;
}

char ReadButton(FILE* f)
{
  if (digitalRead(buttonPin) == BUTTON_ON)
  {
    return '1';
  }
  else
  {
    return '0';
  }
}
