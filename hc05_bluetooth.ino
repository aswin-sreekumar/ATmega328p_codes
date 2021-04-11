// AVR code to interface HC05 bluetooth module
// Send 'a' to turn on LED at PB1 and 'b' to turn it off
// Uses polling for receiving data

#include<avr/io.h>
#define F_CPU 16000000
#define BAUD 9600
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1)  // Baud rate of 9600 programmed.

char data = 0;

char rec_char()
{
  while(!(UCSR0A&(1<<RXC0)));   // Wait for data to be received
  return UDR0;
}

int main()
{
  DDRB|=0b00000010;
  PORTB|=0b00000010;
  UBRR0L = (BAUDRATE);     // Set the required baud rate, upper register
  UBRR0H = (BAUDRATE>>8);  // Set the required baud rate, lower register
  UCSR0B|= (1<<RXEN0);              // Enable reception 
  UCSR0C|= (1<<UCSZ01)|(1<<UCSZ00); // Frame of 8 bits with 1 stop bit
  while(1)
  {
    data = rec_char();
    if(data == 'a')
      PORTB|= 0b00000010;
    else
      PORTB&= ~0b00000010;
  }
  return 0;
}
