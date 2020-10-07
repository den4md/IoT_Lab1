#include "button.h"
#include "led.h"

#define BUTTON_PIN 12
#define LED_PIN 13

#define BUTTON_ON LOW
#define BUTTON_OFF HIGH

#define LED_ON HIGH
#define LED_OFF LOW

#define BUTTON_IDLE 0
#define BUTTON_PRESSED_OR_NOISE 1
#define BUTTON_HOLD 2

#define NOISE_VERIFY_DELAY_MS 100

int led_current_state = LED_OFF;
int button_current_state = BUTTON_IDLE;

unsigned long button_pressed_time = 0;

void setup()
{
  ButtonInit(BUTTON_PIN);
  LedInit(LED_PIN);
}

void switch_led_state()
{
  if (led_current_state == LED_OFF)
    {
      digitalWrite(LED_PIN, LED_ON);
      led_current_state = LED_ON;
    }
    else
    {
      digitalWrite(LED_PIN, LED_OFF);
      led_current_state = LED_OFF;
    }
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == BUTTON_ON)
  {
//    delay(20);
//    if (digitalRead(BUTTON_PIN) == BUTTON_ON)
//    {
//      switch_led_state();
//
//      while (digitalRead(BUTTON_PIN) == BUTTON_ON);
//    }
    if (button_current_state == BUTTON_IDLE)
    {
      button_pressed_time = millis();
      button_current_state = BUTTON_PRESSED_OR_NOISE;
    }
    else if (button_current_state == BUTTON_PRESSED_OR_NOISE && (millis() - button_pressed_time >= NOISE_VERIFY_DELAY_MS))
    {
      button_current_state = BUTTON_HOLD;
      switch_led_state();
    }
  }
  else
  {
    if (button_current_state == BUTTON_HOLD ||
      (button_current_state == BUTTON_PRESSED_OR_NOISE && (millis() - button_pressed_time >= NOISE_VERIFY_DELAY_MS)))
    {
      button_current_state = BUTTON_IDLE;
    }
  }
}
