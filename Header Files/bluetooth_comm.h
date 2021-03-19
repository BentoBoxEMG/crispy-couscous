#ifndef BLUETOOTH_COMM
#define BLUETOOTH_COMM

void uart_transmit(unsigned char);
void bt_send(bt_packet * packet);


// DECIDE HOW THIS WILL BE DEFINED!!!!
sd_packet bt_prepare(processed_data * data);

#endif