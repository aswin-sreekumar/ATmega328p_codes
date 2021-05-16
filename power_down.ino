// AVR code for Atmega328p in power down mode
// Blinks an LED at PB0 - PIN 14 for 2 sec and goes to sleep
// Woken up using external interrupt at INT0 - PIN 4 - PD2
// ADC disabled

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

ISR(INT0_vect)
{  
  SMCR &= ~(1);     // Disable sleep mode
}

int main()
{
  DDRB|=0b00000001;   // PB0 as output
  PORTB|=0b00000001;  // PB0 switched ON
  SMCR |= (1<<SM1);   // Set sleep mode
  ADCSRA &= ~(1<<ADEN); // Disabling ADC
  PRR = 0xFF;           // Disabling all features
  sei();                // Enabling global interrupts
  EIMSK|= (1<<INT0);  // Enable INT0
  EICRA|= (1<<ISC01); // Low Level trigger
  while(1)            // infinite loop
  {  
    PORTB^=0b00000001; // Toggle PB0
    SMCR |= 1;          // Enable Sleep mode
    asm volatile("SLEEP");    // Assembler directive for uC to sleep    
  } 
  return 0;
}
