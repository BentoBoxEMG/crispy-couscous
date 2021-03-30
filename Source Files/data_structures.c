#include "data_structures.h"
#include "ads7951.h"

void process_data(adc_data * data) 
{
    /* Process raw data:
    * This function converts the raw data (measured from the ADC) into its
    * so-called processed form for each of the channels of the ADC.
    * 
    * The conversion is: uint16_t -> unsigned char[NUM_DIGITS_DECIMAL]
    * The conversion is from an unsigned 16-bit integer to an unsigned character array
    * of NUM_DIGITS_DECIMAL. In the case of a 12-bit ADC the maximum value of the integer
    * is 4095, therefore the maximum number of digits is 4. Each of the four digits in the
    * integer is then converted to its character form -- an example of conversion for a 
    * single channel is provided below:
    * 
    *   raw_data = 1024 -> processed_data = ['1','0','2','4']
    *
    */
    for (int i = 0; i < CHANNEL_NUM; i++) 
    {
        uint16_t raw_data = (*data)[i].raw_data;
        sprintf((*data)[i].processed_data, "%04d", raw_data);
    }
}

bt_packet bt_prepare(adc_data * data) 
{
    bt_packet output = {0};
    output.size = CHANNEL_NUM * NUM_DIGITS_DECIMAL + CHANNEL_NUM + NUM_END_CHARS;
    
    for (int i = 0; i < CHANNEL_NUM; i++) 
    {
        output.data[i*(NUM_DIGITS_DECIMAL + 1)] = 'A';
        for (int j = 1; j < NUM_DIGITS_DECIMAL + 1; j++)
        {
            int index = i * (NUM_DIGITS_DECIMAL + 1) + j;
            unsigned char num = (*data)[i].processed_data[j - 1];
            output.data[index] = num;
        }
    }
    output.data[output.size-1] = '\n';
    
    return output;
}

sd_packet sd_prepare(adc_data * data) 
{

}

void adc_get_data(adc_data * data)
{
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        adc_channel sampled_channel = ads7951_auto_one_get_sample();
        (*data)[sampled_channel.ch_number] = sampled_channel;
    }
}