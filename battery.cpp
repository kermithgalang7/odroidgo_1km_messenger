#include <odroid_go.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>

#include "battery.h"

static esp_adc_cal_characteristics_t adc_chars;
double battery_level = 0;
int battery_debounce = 100;

void battery_level_init(void)
{
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
  esp_adc_cal_characterize(
    ADC_UNIT_1, 
    ADC_ATTEN_DB_11, 
    ADC_WIDTH_BIT_12, 
    DEFAULT_VREF, 
    &adc_chars);
}
double get_battery_level(void)
{
  return battery_level;
}
int battery_level_service(void)
{
  uint32_t adc_reading = 0;
  
  if(battery_debounce <= 100)
  {
    battery_debounce++;
    return 0;
  }
  else
    battery_debounce = 0;

  for(int i = 0; i < NO_OF_SAMPLES; i++)
  {
    adc_reading += adc1_get_raw((adc1_channel_t) ADC1_CHANNEL_0);
  }
  adc_reading /= NO_OF_SAMPLES;
  battery_level = (double) esp_adc_cal_raw_to_voltage(adc_reading, &adc_chars) *
    RESISTANCE_NUM / 1000;
  
  return 0;
}
