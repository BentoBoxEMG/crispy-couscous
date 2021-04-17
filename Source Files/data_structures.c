#include "data_structures.h"
#include "ads7951.h"

void process_data(adc_data * data) 
{
    /* process_data:
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
    */
   
    for (int i = 0; i < CHANNEL_NUM; i++) 
    {
        uint16_t raw_data = (*data)[i].raw_data;
        sprintf((*data)[i].processed_data, "%04d", raw_data);
    }
}

bt_packet bt_prepare(adc_data * data) 
{
    /* bt_prepare:
    * This function converts from the adc_data data structure (custom data type) to 
    * the bt_packet data structure (custom data type). 
    * 
    * This conversion can be thought of as a conversion from a matrix of size (CHANNEL_NUM x NUM_DIGITS_DECIMAL)
    * to a 1D array of size (CHANNEL_NUM * NUM_DIGITS_DECIMAL + CHANNEL_NUM + NUM_END_CHARS).
    * 
    * Concretely: 
    * if CHANNEL_NUM = 8, NUM_DIGITS_DECIMAL = 4; NUM_END_CHARS = 1;
    * then the transformation is from a matrix of size (8 x 4) -> to a 1D array of size (41). 
    * 
    */

    // Creates a variable 'output' of type bt_packet and initializes the members to 0.
    bt_packet output = {0};
    // Defines the size member of the output variable. The size is defined to be CHANNEL_NUM * NUM_DIGITS_DECIMAL + CHANNEL_NUM + NUM_END_CHARS.
    // The size member is equal to the size of the data array in the packet.
    output.size = CHANNEL_NUM * NUM_DIGITS_DECIMAL + CHANNEL_NUM + NUM_END_CHARS;
    
    /*
    * This iterates through the data member of the output variable. The two loops iterate a total of CHANNEL_NUM * NUM_DIGITS_DECIMAL
    * times, with the outer loop iterating CHANNEL_NUM times, and the inner loop iterates NUM_DIGITS_DECIMAL times per outer iteration.
    * 
    * Every outer loop iteration the following pattern is written to output.data: 'A',X1,X2,..,Xn. 
    * Where X1,X2,..,Xn are numbers in character form, where n is equal to the NUM_DIGITS_DECIMAL. X1,X2,..Xn are read
    * from the processed_data member of the adc_data variable pointed to by data.
    * 
    * Concretely: 
    * if NUM_DIGITS_DECIMAL = 4,
    * then every outer loop iteration the following pattern will be written to output.data: 'A',X1,X2,X3,X4.
    * 
    */
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
    // Appends the new line character to the end of the data array.
    output.data[output.size-1] = '\n';
    
    return output;
}

// This is incomplete since datalogging is not implemented. 
sd_packet sd_prepare(adc_data * data) 
{

}

// void adc_get_data(adc_data * data)
// {
//     for (int i = 0; i < CHANNEL_NUM; i++)
//     {
//         adc_channel sampled_channel = ads7951_auto_one_get_sample();
//         (*data)[sampled_channel.ch_number] = sampled_channel;
//     }
// }