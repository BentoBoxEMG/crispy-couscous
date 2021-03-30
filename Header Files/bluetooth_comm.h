#ifndef BLUETOOTH_COMM
#define BLUETOOTH_COMM

void uart_transmit(unsigned char);
void bt_send(bt_packet * packet);

#endif
