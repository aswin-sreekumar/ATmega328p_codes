// AVR code for CTC square wave of 8 hz 
// Square wave output at PB1 - OC1A

#include<avr/io.h>

int main()
{
  DDRB|= 0b00000010;
  TCCR1B|= (1<<CS10)|(1<<CS12)|(1<<WGM12);  // CTC mode 1024 prescaler
  TCCR1A|= (1<<COM1A0);                     // Toggling on compare match
  OCR1A = 0x07A1;                           // Set frequency
  while(1);
  return 0;
}
