#include <Keypad.h>

Keypad *keypad;

void begin_keypad(Keypad *k)
{
  keypad = k;
}

char keypad_get_char(FILE *f)
{
  char key;
  do
  {
    key = keypad->getKey();
  }while (key == 0);
  return key;
}
