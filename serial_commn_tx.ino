// AVR code for serial communication through UART 
// Continously transmits string
// Atmega328p microcontroller

#include<avr/io.h>

#define F_CPU 16000000
#define BAUD 9600
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1)  // Baud rate of 9600 programmed.

char str[13] = "hello world\n";
int i = 0;

int main()
{
  UBRR0L = (BAUDRATE);     // Set the required baud rate, upper register
  UBRR0H = (BAUDRATE>>8);  // Set the required baud rate, lower register
  UCSR0B|= (1<<TXEN0);              // Enable TRANSMISSION
  while(1)
  {
     for(i=0;i<strlen(str);i++)   // Loop through the string
     {
      while (!( UCSR0A & (1<<UDRE0)));  // Wait till buffer is empty
      UDR0 = str[i];    // Load the character to be transmitted
     }     
  }
  return 0;
}
