// AVR code - ATmega328p
// PB0 = PD7

#include<avr/io.h>
int a = 0;
int main()
{
  DDRD&= ~0b10000000;
  DDRB|= 0b00000001;
  while(1)
  {
    //PORTB = (PIND7&1)<<0;
    a = ((PIND>>7)&1)<<0;
    PORTB=a;
  }
  return 0;
}
