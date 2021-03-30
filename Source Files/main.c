/* MCU configuration*/
#define F_CPU 16000000UL
#define BAUD 115200

#include <avr/io.h>
#include <util/delay.h>
#include <xc.h>
#include <stdio.h>

#include "data_structures.h"
#include "spi.h"
#include "initialize.h"
#include "ads7951.h"
#include "bluetooth_comm.h"

int main(void) {
    
    clock_init();
    uart_init();
    spi_init();
    
    // Begin ADC operation.
    PORTB &= ~(1 << PORTB2); // Manual mode, channel 0.
    spi_write_byte(0x10);
    spi_write_byte(0x00);
    PORTB |= (1 << PORTB2);
    
    // Switch ADC to Auto-1 mode.
    ads7951_auto_one_register_write();
    
    // Start operation in Auto-1 mode.
    PORTB &= ~(1 << PORTB2); // Use frame to enter Auto-1 mode.
    spi_write_byte(0x28);
    spi_write_byte(0x40);
    PORTB |= (1 << PORTB2);
    
    PORTB &= ~(1 << PORTB2); // Magic.
    spi_write_byte(0x20);
    spi_write_byte(0x00);
    PORTB |= (1 << PORTB2);
    
    adc_data sample_data;
    bt_packet wireless_packet;
    
    while(1)
    {
        adc_get_data(&sample_data);
        process_data(&sample_data);
        wireless_packet = bt_prepare(&sample_data);
        bt_send(&wireless_packet);
        uart_transmit('\r');
        _delay_ms(1000);
    }
    return 0;
}
