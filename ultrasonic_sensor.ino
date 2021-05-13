//interfacing ultrasonic sensor
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

int t=0,i=0;
float w=0;

void init()
{
  Serial.begin(9600);
  DDRD=0b11111011;
  EIMSK=(1<<INT0);
  EICRA=(1<<ISC00);
}

ISR(INT0_vect)
{
  if(i==0) //ECHO goes high
  {
    TCNT1=0;
    TCCR1B=(1<<CS02);
    i=1;
  }
  else //ECHO goes low
  {
    TCCR1B=0;
    t=TCNT1;
    i=0;
  }
}

int main()
{
  init();
  sei();
  while(1)
  {
  PORTD|=(1<<4);
  _delay_us(15);
  PORTD&=~(1<<4);
  w=0.343*t;
  Serial.println(w);
  }
  return 0;
}
