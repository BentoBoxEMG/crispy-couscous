#ifndef BLUETOOTH_COMM
#define BLUETOOTH_COMM

void uart_transmit(unsigned char);
void bt_send(unsigned char * bt_packet, int size);


// DECIDE HOW THIS WILL BE DEFINED!!!!
// unsigned char bt_prepare();

#endif
