#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRB|=0b00000001;
  PORTB|=0b00000001;
  while(1)
  {
    _delay_ms(1000);
    PORTB^=0b00000001;
  }
  return 0;
}
