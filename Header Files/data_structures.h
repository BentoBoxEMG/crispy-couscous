#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#include <stdint.h>
#include <stdio.h>

#define CHANNEL_NUM 8
#define NUM_DIGITS_DECIMAL 4
#define NUM_END_CHARS 1

typedef struct adc_channel_data
{
    uint8_t ch_number; 
    uint16_t raw_data;
    unsigned char processed_data[NUM_DIGITS_DECIMAL];
} adc_channel;

typedef adc_channel adc_data[CHANNEL_NUM];

typedef struct bt_packet
{
    int size;
    unsigned char data[CHANNEL_NUM * NUM_DIGITS_DECIMAL + CHANNEL_NUM + NUM_END_CHARS];
} bt_packet;

typedef struct sd_packet
{
    int size;
    // This is set to the same size as the bt_packet as a fill in.
    unsigned char data[CHANNEL_NUM * NUM_DIGITS_DECIMAL + CHANNEL_NUM + NUM_END_CHARS];
} sd_packet;

void adc_get_data(adc_data * data);
void process_data(adc_data * data);
bt_packet bt_prepare(adc_data * data);
sd_packet sd_prepare(adc_data * data);
#endif
