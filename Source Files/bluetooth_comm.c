#include "bluetooth_comm.h"
#include "data_structures.h"

void uart_transmit(unsigned char data)
{
    while ( !( UCSR0A & (1 << UDRE0)) )
    {
        // Spin wait.
    }
  
    UDR0 = data;   
}

void bt_send(bt_packet * packet)
{
    /* BT_SEND
     * This functions reads data from the bt_packet array and transmits
     * using the UART.
     */

    int i = 0;
    int size = packet -> size;
    while (i < size)
    {
        uart_transmit(*(packet -> data + i));
        i++;
    }
}
