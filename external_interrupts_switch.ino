// AVR code for external interrupts
// PB1 toggles upon LOW LEVEL at INT0 - PD2
// Works effectively with capacitor between digital input and Vcc for hardware debouncing.

#include<avr/io.h>
#include<avr/interrupt.h>

ISR(INT0_vect)
{
  PORTB^=0x02;
}

int main()
{
  DDRB|=0x02;
  PORTB|=0x02;
  sei();              // Enable global interrupts
  EIMSK|= (1<<INT0);  // Enable INT0
  EICRA|= (1<<ISC01); // Low Level trigger
  while(1);
  return 0;
}
