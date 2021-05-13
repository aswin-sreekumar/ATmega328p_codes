// AVR code for serial communication through UART 
// Receives/ transmits string using polling
// Atmega328p microcontroller
// LED at PB0-PIN14, Baud rate of 9600

#include<avr/io.h>

#define F_CPU 16000000
#define BAUD 9600
#define BAUDRATE (((F_CPU / (BAUD * 16UL))) - 1)  // Baud rate of 9600 programmed.

char tx_str[13] = "ENTER CHAR:", rx_str[13];
int i = 0;

void uart_tx(char data)         // Function to transmit character
{
  while (!( UCSR0A & (1<<UDRE0)));  // Wait till buffer is empty
  UDR0 = data;    // Load character to be transmitted
}

char uart_rx()
{
  while (!( UCSR0A & (1<<RXC0)));   // Wait till buffer is full
  return UDR0;    // Return thje received character
}

int main()
{
  DDRB|=0b00000001;
  PORTB = 0x00;
  UBRR0L = (BAUDRATE);     // Set the required baud rate, upper register
  UBRR0H = (BAUDRATE>>8);  // Set the required baud rate, lower register
  UCSR0B|= (1<<TXEN0)|(1<<RXEN0);       // Enable TRANSMISSION and RECEPTION
  while(1)
  {
    for(i=0; tx_str[i]!=0; i++)     // Print required string
      uart_tx(tx_str[i]);
    for(i=0; rx_str[i-1]!='\n'; i++)  // Get required input string, terminates at \n
      rx_str[i] = uart_rx();
      rx_str[i] = '\0';       // Adds null terminator at end of string to avoid errors
    for(i=0; rx_str[i]!=0; i++)     // Prints the input string
      uart_tx(rx_str[i]);
    if(strcmp(rx_str,"ON\n")==0)    // Switch on LED at PB0 when input string is ON
      PORTB|=0x01;
    else if(strcmp(rx_str,"OFF\n")==0)  // Switch off LED at PB0 when input string is OFF
      PORTB &= ~(0x01);
  }
  return 0;
}
