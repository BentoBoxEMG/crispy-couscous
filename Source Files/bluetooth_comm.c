#include "bluetooth_comm.h"

void uart_transmit(unsigned char data)
{
    while ( !( UCSR0A & (1 << UDRE0)) )
    {
        // Spin wait.
    }
  
    UDR0 = data;   
}

void bt_send(unsigned char *, int size)
{

}