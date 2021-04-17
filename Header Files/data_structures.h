#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#include <stdint.h>
#include <stdio.h>

#define CHANNEL_NUM 8
#define NUM_DIGITS_DECIMAL 4
#define NUM_END_CHARS 1



// This data structure (custom data type) represents a single channel of the ADC. It contains data read from
// the ADC and stores it in adc_channel. The ch_number member stores the channel number. The raw_data member
// stores the raw data read from the ADC, this is a 12-bit number but it will be stored as a 16-bit number.
// The processed_data member contains the transformed form of the raw_data. 
typedef struct adc_channel_data
{
    uint8_t ch_number; 
    uint16_t raw_data;
    unsigned char processed_data[NUM_DIGITS_DECIMAL];
} adc_channel;

// This data structure (custom data type) is an array of adc_channels. 
// A pointer to a variable of type adc_data is a pointer to the array, defrefrencing the pointer will allow you
// to index it.
typedef adc_channel adc_data[CHANNEL_NUM];

// This data structure (custom data type) represents the bluetooth packet. It consists of a size member representing the size
// of the data member. The data memeber is an array of unsigned characters containing the data that will be transmitted via
// bluetooth.
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

// void adc_get_data(adc_data * data);

// This function converts the raw data (measured from the ADC) into its so-called processed form
// for each of the channel of the ADC.
void process_data(adc_data * data);

// This function creates the bt_packet data structure from the adc_data data structure.
bt_packet bt_prepare(adc_data * data);

// This function is incomplete since datalogging is not implemented.
sd_packet sd_prepare(adc_data * data);

#endif
