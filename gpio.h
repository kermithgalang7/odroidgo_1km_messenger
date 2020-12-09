#ifndef __GPIO_H__
#define __GPIO_H__

#define GPIO_PIN2           18  //cannot use, shared with SPI lcd/sdcard
#define GPIO_PIN3           12
#define GPIO_PIN4           15
#define GPIO_PIN5           4
#define GPIO_PIN7           19  //cannot use, shared with SPI lcd/sdcard
#define GPIO_PIN8           23  //cannot use, shared with SPI lcd/sdcard


void input_init(void);
void input_service(void);

#endif //__GPIO_H__
