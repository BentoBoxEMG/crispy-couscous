#include <stdio.h>
#include <stdint.h>

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

int main() 
{
    adc_data ADC_DATA = {0};
    adc_data * ADC_DATA_ptr = &ADC_DATA;

    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        ADC_DATA[i].raw_data = i*100;
        sprintf((*ADC_DATA_ptr)[i].processed_data,"%04d",(*ADC_DATA_ptr)[i].raw_data);
        for (int j = 0; j < NUM_DIGITS_DECIMAL; j++)
        {
            printf("%c\t",(*ADC_DATA_ptr)[i].processed_data[j]);
        }
        printf("%d\n",ADC_DATA[i].raw_data);
    }

    bt_packet output = {0};
    output.size = CHANNEL_NUM * NUM_DIGITS_DECIMAL + CHANNEL_NUM + NUM_END_CHARS;

    for (int i = 0; i < CHANNEL_NUM; i++) 
    {
        output.data[i*(NUM_DIGITS_DECIMAL + 1)] = 'A';
        for (int j = 1; j < NUM_DIGITS_DECIMAL + 1; j++) 
        {
            int index = i * (NUM_DIGITS_DECIMAL + 1) + j ;
            unsigned char num = (*ADC_DATA_ptr)[i].processed_data[j - 1];
            output.data[index] = num;
        }
    }
    output.data[output.size-1] = '\n';
    bt_packet * output_ptr = &output;

    // for (int i = 0; i < output_ptr->size; i++) 
    // {
    //     printf("%c",output_ptr->data[i]);
    // }
    int i = 0;
    while (i < output_ptr->size)
    {
        printf("%c",output_ptr -> data[i]);
        i++;
    }
    printf("Hello World");

    // for (int i = 0; i < CHANNEL_NUM; i++) 
    // {
    //     for (int j = 0; j < NUM_DIGITS_DECIMAL; j++) 
    //     {
    //         int num = i*(NUM_DIGITS_DECIMAL + 1) + j + 1;
    //         printf("%d ", num);
    //         // unsigned char num = (*ADC_DATA_ptr)[i].processed_data[j];
    //         // output.data[i*NUM_DIGITS_DECIMAL + j] = num;
    //         // printf("%c ",output.data[i*NUM_DIGITS_DECIMAL+j]);
    //     }
    // }

}