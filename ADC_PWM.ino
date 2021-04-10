// AVR code to implement PWM duty cycle proportional to ADC
// PWM generated using OC0 mode timer 0, OC0A set on compare match and clear at BOTTOM
// PWM output - OC0A - PD6
// ADC input - ADC5 - PC5

#include<avr/io.h>

int a = 0;
int ADC_convert()
{
  ADCSRA|=(1<<ADSC);
  while(ADCSRA&(1<<ADSC));
  return ADC;
}

int main()
{
  DDRD|= 0b01000000;  
  ADMUX=(1<<REFS0)|(1<<MUX2)|(1<<MUX0);               // Internal Vref, ADC5
  ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);  // Prescaler 128
  TCCR0A|=(1<<COM0A1)|(1<<COM0A0)|(1<<WGM01)|(1<<WGM00);  // Fast PWM, OC0A used in inverting mode
  TCCR0B|=(1<<CS02);  // Prescaler of 256
  while(1)
  {
    a = ADC_convert();
    OCR0A = a/4;
  }
  return 0;
}
