/* MCU configuration*/
#define F_CPU 16000000UL
#define BAUD 115200

#include <avr/io.h>
#include <util/delay.h>

void spi_init(unsigned int);
void uart_init();
void uart_transmit(unsigned char);
void clock_init();

int main(void) 
{
//    This is code used to control an LED, remove this when deploying in a non-
//    testing capacity
    DDRB |= (1 << DDB0);
    
    /* Initialization code:
     * This consists of two parts (at the moment) first the clock division fact-
     * or is changed to 1. This is achieved by first setting CLKPCE to one,
     * and then setting CLKPCE to 0 and by setting CLKPS bits to 0.
     * 
     * The second part is consists of initializing the UART (check function doc)
     */
    
    // Initialize clock division.
//    CLKPR = (1<<CLKPCE);
//    CLKPR = 0;
    clock_init();
    // UART initialization.
    uart_init();
    
//    unsigned char num = 0x6E;
    unsigned char seperator = 'A';
//    unsigned char num = 0x41;
    unsigned char num = 0x31;


    while (1) 
    {
//        PORTB |= (1<<PORTB0);
//        _delay_ms(1000);
//         PORTB &= ~(1<<PORTB0);
        _delay_ms(1000);
//        if (num != 0x60){
//            uart_transmit(num);
//            num += 1;
//            uart_transmit('\n');
//        }
//        else{
//            _delay_ms(10000);
//            num = 0x41;
//        }
        uart_transmit(seperator);
        uart_transmit(num);
        uart_transmit(seperator);
        uart_transmit(num);
        uart_transmit(seperator);
        uart_transmit(num);
        uart_transmit(seperator);
        uart_transmit(num);
        uart_transmit(seperator);
        uart_transmit(num);
        uart_transmit(seperator);
        uart_transmit(num);
        uart_transmit(seperator);
        uart_transmit(num);
        uart_transmit(seperator);
        uart_transmit(num);
        uart_transmit('\n');
//        _delay_ms(1000);
    }
}

void uart_init()
{
    /* UART initialization:
     * This consists of setting the baud rate, enabling receiver and transmitter,
     * and setting frame format.
     * 
     * The baud rate, i.e. UBRRn is set to 8 (check table 20-7 of 328P docs).
     * To set UBRRnH is set to 0xF0, and UBRRnL is set to 0x08.
     * 
     * To enable the transmitter and receiver, TXEN0 and RXEN0 bits of UCSR0B 
     * must be set. 
     * 
     * The data frame format must be set to be 8-bits long, no parity, with 1 
     * stop bit. To do this UPM01, UPM00, USBS0, UCSZ02 bits of UCSR0C is set to 0.
     * UCSZ01 and UCSZ00 bits of UCSR0C are set to 1.
     * 
    */

    // Setting of the baud rate.
    UBRR0H &= 0xF0;
    UBRR0L = 0x08;
    
    // Enable transmitter and receiver.
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    
    // 8N1 frame format is enabled by default.
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
//    UCSR0C = 0x06;

}

void uart_transmit(unsigned char data)
{
    while ( !( UCSR0A & (1 << UDRE0)) )
    {
        // Spin wait.
    }
  
    UDR0 = data;   
}

void clock_init()
{
    // Initialize clock division.
    CLKPR = (1<<CLKPCE);
    CLKPR = 0;
}