#include <stdio.h>

#include "timer-api.h"
#include "button.h"
#include "led.h"

#define BUTTON_PIN 2
#define INTERRUPT 0  // for 0 - button pin 2, for 1 - 3
#define LED_PIN 13

#define TIMER_FREQUENCY timer_init_ISR_20Hz

volatile int timer = TIMER_DEFAULT;

int led_current_state = LED_OFF;

unsigned long button_pressed_time = 0;

char helpChar = '-';

void setup()
{
  Serial.begin(9600);
  ButtonInit(BUTTON_PIN);
  LedInit(LED_PIN);

  FILE *stream = fdevopen(WriteLed, ReadButton);
  stdin = stdout = stream;

  attachInterrupt(INTERRUPT, externalInterrupt, CHANGE);
}

void switchLedState()
{
  if (led_current_state == LED_OFF)
    {
      printf("%c", '1');
      led_current_state = LED_ON;
    }
    else
    {
      printf("%c", '0');
      led_current_state = LED_OFF;
    }
}

void externalInterrupt()
{
  timer_stop_ISR(timer);  // stops previous timer
  TIMER_FREQUENCY(timer);  // initializes new timer
}

void timer_handle_interrupts(int timer)
{
  detachInterrupt(INTERRUPT);

  scanf("%c", &helpChar);
  if (helpChar == '1')
  {
    switchLedState();
  
    while (true)
    {
      scanf("%c", &helpChar);
      if (helpChar == '0')
      {
        break;
      }
    }
  }

  attachInterrupt(INTERRUPT, externalInterrupt, CHANGE);
  timer_stop_ISR(timer);
}

void loop() { }
