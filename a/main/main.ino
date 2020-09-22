#include "button.h"
#include "led.h"

#define BUTTON_PIN 12
#define LED_PIN 13

#define BUTTON_ON LOW
#define BUTTON_OFF HIGH

#define LED_ON HIGH
#define LED_OFF LOW

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
      delay(20);
      if (digitalRead(BUTTON_PIN) == BUTTON_ON)
      {
        if (current_state == LED_OFF)
        {
          digitalWrite(LED_PIN, LED_ON);
          current_state = LED_ON;
        }
        else
        {
          digitalWrite(LED_PIN, LED_OFF);
          current_state = LED_OFF;
        }
        
        while (digitalRead(BUTTON_PIN) == BUTTON_ON);
      }
  }
}
