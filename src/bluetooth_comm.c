#include "bluetooth_comm.h"
#include <avr/io.h>

void uart_transmit(unsigned char data)
{
    while ( !( UCSR0A & (1 << UDRE0)) )
    {
        // Spin wait.
    }
  
    UDR0 = data;   
}

void bt_send(unsigned char * bt_packet, int size)
{
    /* BT_SEND
     * This functions reads data from the bt_packet array and transmits
     * using the UART.
     */

    int i = 0;

    while (i < size)
    {
        uart_transmit(*(bt_packet + i));
        i++;
    }
}
