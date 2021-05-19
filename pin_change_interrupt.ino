// AVR code for PIN state change interrupt
// Also verifies the required pin
// PIN 2 - PCINT16
// Atmega328p

#include<avr/io.h>
#include<avr/interrupt.h>

ISR(PCINT2_vect)
{
  if(!(PIND&0x01))
    PORTB = 0x01;
  else
    PORTB = 0x00;
}

int main()
{
  DDRB |= 0x01;
  PORTB |= 0x01;
  DDRD &= ~0x01;  // Set PCINT16 as input
  PORTD |= 0x01;  // Pull up PCINT pin
  PCMSK2 = (1 << PCINT16);  // set PCINT16 to trigger an interrupt on state change
  PCICR = (1 << PCIE2);    // set PCIE2 to enable PCMSK0 scan
  sei();
  while(1);
  return 0;
}
