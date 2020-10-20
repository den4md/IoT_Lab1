#include <string.h> 
#include <stdio.h>
#include "led.h"
#include "serial.h"

#define LED_PIN 13
#define LED_ON HIGH
#define LED_OFF LOW

#define COMMAND_ON "led on"
#define COMMAND_OFF "led off"

char* last_word = new char[256];
int helping_index = 0;

int current_state = LED_OFF;


void setup()
{
  FILE *my_stream = stdio_init();
  stdin = stdout = my_stream;
  Serial.begin(9600);
  LedInit(LED_PIN);
  //Serial.setTimeout(0);
}

void scan_newline()
{
  //printf("\r\n-start scan\r\n");
  for(helping_index = 0; helping_index < 256; ++helping_index)
  {
    last_word[helping_index] = '\0';
  }
  char c;
  
  while(!Serial.available());
  
  helping_index = 0;
  scanf("%c", &c);
  while ((c != '\n') && (c != '\r') && (helping_index < 256))
  {
    printf("%c", c);
    //printf("\r\n----------------------------\r\n");
    if (c == 8)
    {
      if (helping_index != 0)
      {
        --helping_index;
        last_word[helping_index] = '\0';
      }
      scanf("%c", &c);
      continue;
    }
    last_word[helping_index] = c;
    ++helping_index;
    scanf("%c", &c);
  }
  printf("\r\n");
  //printf("\r\n-stopped scan\r\n");
}

void beautify()
{
  for (int i = 0; (i < 256) && (last_word[i] != '\0'); ++i)
  {
    switch (last_word[i])
    {
      case 'L': last_word[i] = 'l'; break;
      case 'E': last_word[i] = 'e'; break;
      case 'D': last_word[i] = 'd'; break;
      case 'O': last_word[i] = 'o'; break;
      case 'N': last_word[i] = 'n'; break;
      case 'F': last_word[i] = 'f'; break;
    }
  }
}

void loop()
{
  //printf("\r\n-in loop\r\n");
  printf("@: ");
  scan_newline();
  //printf(last_word);
  beautify();
  if (strcmp(last_word, COMMAND_ON) == 0)
  {
    if (current_state == LED_ON)
    {
      printf("<System>: LED is already on\r\n");
    }
    else
    {
      digitalWrite(LED_PIN, LED_ON);
      current_state = LED_ON;
      printf("<System>: Turned LED on\r\n");
    }
  }
  else if (strcmp(last_word, COMMAND_OFF) == 0)
  {
    if (current_state == LED_OFF)
    {
      printf("<System>: LED is already off\r\n");
    }
    else
    {
      digitalWrite(LED_PIN, LED_OFF);
      current_state = LED_OFF;
      printf("<System>: Turned LED off\r\n");
    }
  }
  else
  {
      printf("<System>: Unknown command!\r\n");
  }
  //printf("\r\n-out loop\r\n");
}
