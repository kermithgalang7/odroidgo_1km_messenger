#ifndef __BATTERY_H__
#define __BATTERY_H__

#define RESISTANCE_NUM      2
#define DEFAULT_VREF        1100
#define NO_OF_SAMPLES       64

void battery_level_init(void);
double get_battery_level(void);
int battery_level_service(void);

#endif //__BATTERY_H__
