#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#define CHANNEL_NUM 8

// OLD DATASTRUCTURE DEFINITION
// typedef struct adc_data
// {
//     uint16_t ch1;
//     uint16_t ch2;
//     uint16_t ch3;
//     uint16_t ch4;
//     uint16_t ch5;
//     uint16_t ch6;
//     uint16_t ch7;
//     uint16_t ch8;
// } adc_data;

typedef struct adc_channel
{
    uint16_t data;
} adc_channel;

typedef adc_channel adc_data[CHANNEL_NUM];

typedef struct processed_data
{
    unsigned char ch1[4];
    unsigned char ch2[4];
    unsigned char ch3[4];
    unsigned char ch4[4];
    unsigned char ch5[4];
    unsigned char ch6[4];
    unsigned char ch7[4];
    unsigned char ch8[4];
} processed_data;

typedef struct bt_packet
{
    int size CHANNEL_NUM;
    unsigned char data[41];
} bt_packet;

typedef struct sd_packet
{
    int size;
    // This is set to the same size as the bt_packet as a fill in.
    unsigned char data[41];
} sd_packet;

#endif