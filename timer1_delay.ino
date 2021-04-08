// AVR code for 2+1 sec square wave at pin PB0 using timer1
// ATmega 328p chip

#include<avr/io.h>

void delay_timer(int a=1)
{
  //TCNT1L = 0xF7;
  //TCNT1H = 0xC2;
  TCNT1 = 65536 - (a*15625);
  TCCR1B = (1<<CS12)|(1<<CS10);
  while(!(TIFR1&0x01));
  TCCR1B = 0;
  TIFR1 = 0x01; 
}

int main()
{
  DDRB|= 0b00000001;
  PORTB|= 0b00000001;
  while(true)
  {
    PORTB^=0x01;
    delay_timer(1);
    PORTB^=0x01;
    delay_timer(2);
  }
  return 0;
}
