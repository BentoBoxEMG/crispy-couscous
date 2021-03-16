#include "adc_funcs.h"

void serialMasterInit(){
    // May want to set these registers to zero initially.

    // Set the MOSI(bit 3) and SCK(bit 5) in DDRB.
    DDRB = (1<<5) | (1<<3);
    // Set the SPE (bit 6), MSTR (bit 4), and CPHA (bit 2) bits in SPCR
    // SPE bit enables SPI, MSTR sets the MC to master, and CPHA set sampling
    // at falling edge.
    SPCR = (1<<6)|(1<<4)|(1<<2);
}