// AVR code - ATmega328p - digital output

#include<avr/io.h>

int main()
{
  DDRD|= 0xFF;
  PORTD|= 0xFF;
  return 0;
}
