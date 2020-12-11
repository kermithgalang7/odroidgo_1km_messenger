#ifndef __GPIO_H__
#define __GPIO_H__

#define GPIO_PIN2           18  //cannot use, shared with SPI lcd/sdcard
#define GPIO_PIN3           12
#define GPIO_PIN4           15
#define GPIO_PIN5           4
#define GPIO_PIN7           19  //cannot use, shared with SPI lcd/sdcard
#define GPIO_PIN8           23  //cannot use, shared with SPI lcd/sdcard

#define PIN_BLUE_LED        2
#define PWM_CHANNEL         1
#define PWM_12KHZ           12000
#define PWM_8BIT            8

#define LED_STAT_ON         0
#define LED_STAT_OFF        1
#define LED_STAT_FASTBLINK  2
#define LED_STAT_SLOWBLINK  3
#define LED_STAT_BEATING    4


#define BUT_DEBOUNCE        10
#define BUT_NONE            0
#define BUT_UP              1
#define BUT_DOWN            2
#define BUT_LEFT            3
#define BUT_RIGHT           4
#define BUT_A               5
#define BUT_B               6
#define BUT_MENU            7
#define BUT_VOL             8
#define BUT_SEL             9
#define BUT_START           10

#define BUT_MARK_UP         0x01
#define BUT_MARK_DOWN       0x02
#define BUT_MARK_LEFT       0x04
#define BUT_MARK_RIGHT      0x08

#define BUT_MARK_A          0x01
#define BUT_MARK_B          0x02

#define BUT_MARK_MENU       0x01
#define BUT_MARK_VOL        0x02
#define BUT_MARK_SEL        0x04
#define BUT_MARK_START      0x08


void output_init(void);
void input_init(void);
int consume_input(void);
void input_service(void);
void set_led_stat(int stat);
int led_service(void);


#endif //__GPIO_H__
