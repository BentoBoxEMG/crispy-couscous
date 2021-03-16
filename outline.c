// General firmware outline.

int main(void)
{
    // Setup, power on or reset.
    while(1)
    {
        if (flag = 1)
        {
            set_indicator_led(); // Indicate low battery.   
        }
        adc_reading = sample_adc();
        converted_data = data_conversion(adc_reading);
        bt_packet = bt_prepare(converted_data);
        bt_send(bt_packet); //BT module.
        sd_packet = sd_prepare();
        datalogging(sd_packet); //SD write.
        wait();
    }
}

interrupt1(void) // Every 5 minutes?
{
   check_battery_voltage();
   if (battery_low)
   {
      flag = 1;
   } 
}

struct adc // Used to hold adc readings.
{
    uint16_t ch1; // Binary data.
    uint16_t ch2;
    uint16_t ch3;
    // Other channels.
    uint16_t ch8;
}
