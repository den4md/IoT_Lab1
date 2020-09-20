#include <stdio.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#include "led.h"

#define RED_LED_PIN A0
#define GREEN_LED_PIN A1

#define LED_ON HIGH
#define LED_OFF LOW

#define RS 13
#define EN 12
#define D4 11
#define D5 10
#define D6 1
#define D7 0

#define LCD_X 16
#define LCD_Y 2

#define ROW_NUM 4
#define COLUMN_NUM 4

#define CODE "1337"
#define STRING_LEN LCD_X*LCD_Y

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2};

char keys[ROW_NUM][COLUMN_NUM] = {
  {'7','8','9', 'A'},
  {'4','5','6', 'B'},
  {'1','2','3', 'C'},
  {'*','0','#', 'D'}
};

//byte mark[7] = {
//  0b00000,
//  0b00001,
//  0b00010,
//  0b10100,
//  0b01000,
//  0b00000,
//  0b00000
//};

Keypad *keypad = NULL;
LiquidCrystal *lcd = NULL;

char* string = new char[STRING_LEN];
int pos_x = 0;
int pos_y = 0;

unsigned long time_del = 0;

void clear_string()
{
  for (int i = 0; i < STRING_LEN; ++i)
  {
    string[i] = '\0';
  }
}

void clear_lcd(const char* fill_char = " ")
{
  for (int i = 0; i < LCD_Y; ++i)
  {
    lcd->setCursor(0, i);
    for (int j = 0; j < LCD_X; ++j)
    {
      printf(fill_char);
    }
  }
  lcd->setCursor(0, 0);
  pos_x = 0;
  pos_y = 0;
}

void reset()
{
  clear_lcd();
  clear_string();
}

void lcd_put_char(char ch, FILE *f)
{
  lcd->print(ch);
  return ch;
}

void keypad_get_char(FILE *f)
{
  char key;
  do
  {
    key = keypad->getKey();
  }while (key == 0);
  return key;
}

bool check_answer()
{
  return (strcmp(string, CODE) == 0);
}

void blink_led(int led_pin)
{
  digitalWrite(led_pin, LED_ON);
  delay(750);
  digitalWrite(led_pin, LED_OFF);
}

void right_answer()
{
  blink_led(GREEN_LED_PIN);
}

void wrong_answer()
{
  blink_led(RED_LED_PIN);
}


void keypadEvent(KeypadEvent key);

void setup()
{
  keypad = new Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
  lcd = new LiquidCrystal(RS, EN, D4, D5, D6, D7);
  lcd->begin(16, 2);  
  FILE* stream = fdevopen(lcd_put_char, keypad_get_char);
  stderr = stdout = stdin = stream;

  LedInit(RED_LED_PIN);
  LedInit(GREEN_LED_PIN);
  
  reset();
  keypad->addEventListener(keypadEvent);
//  lcd->createChar(0, mark);
//  lcd->write((byte)0);
//  lcd->display();
}

bool is_hold(char c = '*', int delay_millisec = 1500)
{
  for(int i = 0; i < 10; ++i)
  {
    if (!keypad->isPressed(&c))
    {
      return false;
    }
    
    delay(delay_millisec / 10);
  }
  return true;
}

void delete_char()
{
  if (pos_x == 0 && pos_y == 0)
  {
    return;
  }
  
  string[((pos_y) * LCD_X) + pos_x - 1] = '\0';

  --pos_x;
  if (pos_x < 0)
  {
    pos_x = LCD_X - 1;
    --pos_y;
  }

  lcd->setCursor(pos_x, pos_y);
  printf(" ");
  lcd->setCursor(pos_x, pos_y);
  
  
  
//  clear_lcd();
//  
//  while (string[((pos_y) * LCD_Y) + pos_x] != '\0' && ((pos_x + 1) * (pos_y + 1) < STRING_LEN + 1))
//  {
//    lcd->setCursor(pos_x, pos_y);
//    printf("%c", string[((pos_y) * LCD_Y) + pos_x]);
//    if (pos_x >= LCD_X)
//    {
//      pos_x = 0;
//      pos_y = pos_y + 1;
//    }
//    ++pos_x;
//  }
}


void keypadEvent(KeypadEvent key)
{
  if (key == '*' && keypad->getState() == IDLE)
  {
    if (millis() - time_del < 1000)
    {
      delete_char();
    }
    else
    {
      reset();
    }
  }
}

void loop()
{
  char c;
  scanf("%c", &c);
  if (c == '*') // Стирание строки
  {
    time_del = millis();
  }
  else if (c == '#')  // Проверка кода
  {
    if (check_answer())
    {
      right_answer();
    }
    else
    {
      wrong_answer();
    }
  }
  else if ((pos_x + 1) * (pos_y + 1) < STRING_LEN + 1)
  {
    if (pos_x >= LCD_X)
    {
      pos_x = 0;
      pos_y = pos_y + 1;
      lcd->setCursor(pos_x, pos_y);
    }
    string[((pos_y) * LCD_Y) + pos_x] = c;
    ++pos_x;
    printf("%c", c);
  }
}
