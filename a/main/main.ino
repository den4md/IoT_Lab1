#include "button.h"
#include "led.h"

#define BUTTON_PIN 12
#define LED_PIN 13

#define BUTTON_ON HIGH
#define BUTTON_OFF LOW

#define LED_ON LOW
#define LED_OFF HIGH

void setup()
{
  ButtonInit(BUTTON_PIN);
  LedInit(LED_PIN);
}

int current_state = LED_OFF;

void loop()
{
  if (digitalRead(BUTTON_PIN) == BUTTON_ON)
  {
      delay(200);
      if (current_state == LED_OFF)
      {
        digitalRead(LED_PIN, LED_ON);
      }
      else
      {
        digitalRead(LED_PIN, LED_OFF);
      }
  }
}
