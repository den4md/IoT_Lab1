void my_putChar(char c, FILE *f)
{
  Serial.write(c);
  return c;
}

char my_GetChar(FILE *f)
{
  while(!Serial.available());
  return Serial.read();
}

FILE* stdio_init()
{
  return fdevopen(my_putChar, my_GetChar);
}
