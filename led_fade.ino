// AVR code for LED fading using PWM 
// PWM output at PB1 - OC1A
// PWM generated using Timer 0 PWM mode and timer 2 interrupt for delay

#include<avr/io.h>
#include<avr/interrupt.h>

bool flag = 1;
ISR(TIMER2_OVF_vect)
{
  if(OCR0A==255)
    flag = 0;
  else if(OCR0A==0)
    flag = 1;
  if(flag)
    OCR0A++;
  else
    OCR0A--;
}

int main()
{
  DDRD|=0b01000000;
  TCCR0A|=(1<<WGM00)|(1<<WGM02)|(1<<COM0A1)|(1<<COM0A0);  // Inverting mode phase correct PWM
  TCCR0B|=(1<<CS00); // Prescaler of 4
  sei();
  TCNT2 = 0x00;
  TIMSK2|=(1<<TOIE2);   // Timer 2 interrupt
  TCCR2B|=(1<<CS20)|(1<<CS21)|(1<<CS22);  // Prescaler of 1024
  while(1);
  return 0;
}
