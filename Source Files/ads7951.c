#include <avr/io.h>
#include "spi.h"
#include "data_structures.h"

#define CHANNEL_SELECT 0x07
#define CHANNEL_MASK 0xF0
#define MSN_MASK 0x0F // Mask used on high byte to get top 4 bits of the 
                      // conversion result.

adc_channel ads7951_auto_one_get_sample(void) 
{ 
    uint8_t adc_resp_high; // Stores upper byte of 16-bit response.
    uint8_t adc_resp_low; // Stores lower byte of 16-bit response.
    uint8_t channel; // Stores channel associated with conversion result.
    uint16_t adc_response; // Stores 12-bit conversion result. 
    adc_channel output_struct;
    
    // Pull SS low.
    PORTB &= ~(1 << PB5); 
    
    // Perform data transmission of MSB.
    adc_resp_high = spi_write_byte(0x00);
    
    // Perform data transmission of LSB.
    adc_resp_low = spi_write_byte(0x00);
    
    // Pull SS high.
    PORTB |= (1 << PB5);
    
    // Obtain channel associated with conversion result.
    channel = (adc_resp_low & CHANNEL_MASK) >> 4;
 
    // Assemble response from ADC.
    adc_response = (((uint16_t)adc_resp_high & MSN_MASK) << 8) 
            | adc_resp_low;
    
    // Populate output struct.
    output_struct.ch_number = channel;
    output_struct.raw_data = adc_response;

    return output_struct;
}

void ads7951_auto_one_register_write(void)
{
    PORTB &= ~(1 << PORTB2);
    spi_write_byte(0x80); // Enter Auto-1 program sequence.
    spi_write_byte(0x00); // Device programming performed in next frame.
    PORTB |= (1 << PORTB2);
    
    PORTB &= ~(1 << PORTB2);
    spi_write_byte(0x00); // Do not care about these bits.
    spi_write_byte(CHANNEL_SELECT); // Enable first three channels (0,1,2). 
    PORTB |= (1 << PORTB2);
    
    return;
}
