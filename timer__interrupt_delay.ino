// AVR code for Timer 1 interrupts
// Output LED at PB0

#include<avr/io.h>
#include<avr/interrupt.h>

ISR(TIMER1_OVF_vect)
{
  PORTB^=0x01;
  TCNT1 = 0xC2F7;  
}

int main()
{
  DDRB|=0x01;
  PORTB|=0x01;
  sei();
  TCNT1 = 0xC2F7;
  TIMSK1 = 1<<TOIE1;
  TCCR1B = (1<<CS12)|(1<<CS10);
  while(1);
  return 0;
}
