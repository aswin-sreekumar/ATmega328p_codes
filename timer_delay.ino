// AVR code for 1 sec delay at pin PB0
// Timer0 

#include<avr/io.h>

int i=0;
// Function to create delay
void delay_timer()
{
  TCNT0=0;                      // Load initial value
  TCCR0B=(1<<CS02)|(1<<CS00);   // Set prescaler and start timer0
  while(!(TIFR0&0x01));         // Wait till flag goes up
  TCCR0B=0;                     // Stop timer
  TIFR0=0x01;                   // Clear timer flag
}

int main()
{
  DDRB|=0b00000001;
  PORTB|=0b00000001;
  while(true)
  {
    for(i=0;i<61;i++)
    delay_timer();
    PORTB^=0b00000001;
  }
}
