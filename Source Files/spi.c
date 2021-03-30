#include <avr/io.h>

void spi_init(void) // SS pin is currently hard-coded. 
{
    // Set SS, MOSI, and SCK pins as outputs.
    DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB5);
    // Output high on SS.
    PORTB |= (1 << PB2);

    // Configure SPCR register to enable SPI.
    SPCR |= (1 << SPE);     // Enable SPI.
    SPCR |= (1 << MSTR);    // Operate in Master mode.
    SPCR &= ~(1 << CPOL);   // SPI mode 0.
    SPCR &= ~(1 << CPHA);    // SPI mode 0.
    SPCR &= ~(1 << SPR1) & ~(1 << SPR0); // SCLK set to fosc/4.
    
    return;
}

uint8_t spi_write_byte(uint8_t data)
{
    SPDR = data;
    
    while (!(SPSR & (1 << SPIF)))
    {
        // Wait for transmission to complete.
    }
    
    return SPDR;
}
