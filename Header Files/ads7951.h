#ifndef ADS7951_H
#define	ADS7951_H

#include "data_structures.h"

adc_channel ads7951_auto_one_get_sample(void);
void ads7951_auto_one_register_write(void);
void adc_get_data(adc_data * data);


#endif	

