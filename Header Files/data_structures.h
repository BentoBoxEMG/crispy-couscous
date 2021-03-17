#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

typedef struct
{
    uint16_t ch1;
    uint16_t ch2;
    uint16_t ch3;
    uint16_t ch4;
    uint16_t ch5;
    uint16_t ch6;
    uint16_t ch7;
    uint16_t ch8;
} adc_data;

typedef struct 
{
    int size;
    unsigned char data[41];
} bt_packet;

typedef struct
{
    int size;
    // This is set to the same size as the bt_packet as a fill in.
    unsigned char data[41];
} sd_packet;

#endif