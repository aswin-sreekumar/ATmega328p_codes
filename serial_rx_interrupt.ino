// AVR CODE FOR SERIAL RECEPTION USING INTERRUPTS
// SERIAL COMMUNICATION USING INTERRUPTS
// HC05 INTERFACED WITH ATMEGA328P AT 16MHZ EXTERNAL CRYSTAL
// LED CONNECTED AT PB1
// 'a' - OFF, 'A' - ON

#include<avr/io.h>
#include<avr/interrupt.h>

#define F_CPU 16000000
#define BAUD 9600
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1)  // Baud rate of 9600 programmed.

char data = 0;

ISR(USART_RX_vect)
{
  data = UDR0;  
}

int main()
{
  DDRB |= 0x02;
  PORTB = 0x02;
  sei();
  UBRR0L = (BAUDRATE);     // Set the required baud rate, upper register
  UBRR0H = (BAUDRATE>>8);  // Set the required baud rate, lower register
  UCSR0B|= (1<<RXEN0)|(1<<RXCIE0);              // Enable reception 
  UCSR0C|= (1<<UCSZ01)|(1<<UCSZ00); // Frame of 8 bits with 1 stop bit
  while(1)
  {
    if(data == 65)
      PORTB = 0x02;
    else if(data == 97)
      PORTB = 0x00;
  }
  return 0;
}
