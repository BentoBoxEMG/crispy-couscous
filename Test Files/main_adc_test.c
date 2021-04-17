/*
 * File:   main.c
 * Author: zkwong
 *
 * Created on February 21, 2021, 2:54 PM
 */

#define F_CPU 16000000UL 

#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

#include "spi.h"
#include "initialize.h"
#include "ads7951.h"
#include "bluetooth_comm.h"

void main(void) {
    uint8_t resp_high;
    uint8_t resp_low;
    uint8_t result_low; // Hold hex digit.
    uint8_t result_mid; // Hold hex digit.
    uint8_t result_high; // Hold hex digit.
    char channel_str[] = "Channel: ";
    char analog_str[] = "Analog value: ";
    
    clock_init();
    uart_init();
    spi_init();
    
    PORTB &= ~(1 << PORTB2); // Manual mode, channel 0.
    spi_write_byte(0x10);
    spi_write_byte(0x00);
    PORTB |= (1 << PORTB2);
    
    ads7951_auto_one_register_write();
    
    PORTB &= ~(1 << PORTB2); // Use frame to enter Auto-1 mode.
    spi_write_byte(0x28);
    spi_write_byte(0x40);
    PORTB |= (1 << PORTB2);
    
    while(1)
    {
        PORTB &= ~(1 << PORTB2);
        resp_high = spi_write_byte(0x00);
        resp_low = spi_write_byte(0x00);
        PORTB |= (1 << PORTB2);
        
        result_high = (resp_high & 0x0F);
        result_mid = (resp_low & 0xF0) >> 4;
        result_low = (resp_low & 0x0F);
        resp_high = (resp_high & 0xF0) >> 4;


        for(uint8_t i = 0; channel_str[i] != '\0'; i++)
        {
            uart_transmit(channel_str[i]);
        }
        uart_transmit(resp_high + 0x30);
        uart_transmit('\t');
        for(uint8_t i = 0; analog_str[i] != '\0'; i++)
        {
            uart_transmit(analog_str[i]);
        }
        uart_transmit('0');
        uart_transmit('x');
        uart_transmit(result_high + 0x30);
        uart_transmit(result_mid + 0x30);
        uart_transmit(result_low + 0x30);
        uart_transmit('\n');
        uart_transmit('\r');
 
        _delay_ms(500);
    }
    return;
}
