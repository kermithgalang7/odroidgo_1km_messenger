#include <odroid_go.h>
#include <WiFi.h>

#include "audio.h"
#include "battery.h"
#include "display.h"
#include "gpio.h"
#include "wifi.h"
#include "uart_handler.h"



int program_flow = 0;

void hardware_init(void)
{
  audio_init();
  battery_level_init();
  output_init();
  input_init();
  display_init();  
  uart_handler_init();  
}

void heart_beat()
{
  if(program_flow < 1000000)
    program_flow++;
  else
    program_flow = 0;
}

void setup() {
  // put your setup code here, to run once:
  GO.begin();

  hardware_init();
}

int cinput;
int cdisplay;
void loop() {
  // put your main code here, to run repeatedly:

  cinput = consume_input();
  if(cinput != BUT_NONE)
  {
    run_tone(5);
    disable_interval();
  }
    
  cdisplay = get_display_page();
  switch(cdisplay)
  {
    case DISPLAY_BLANK:
      if(program_flow == 100)
      {
        program_flow = 0;
        set_display_page(DISPLAY_SPLASH);
        push_message_queue("test");
      }
    break;
    case DISPLAY_SPLASH:
      if(program_flow == 100)
      {
        program_flow = 0;
        set_display_page(DISPLAY_MAIN);
        push_message_queue("test1");
//        set_display_page(DISPLAY_DEBUG);
      }
    break;
    case DISPLAY_MAIN:
#if 1
      if(cinput == BUT_MENU)
        set_display_page(DISPLAY_DEBUG);
      if(cinput == BUT_LEFT)
        keyb_left();
      if(cinput == BUT_RIGHT)
        keyb_right();
      if(cinput == BUT_UP)
        keyb_up();
      if(cinput == BUT_DOWN)
        keyb_down();
      if(cinput == BUT_A)
        keyb_ok();
      if(cinput == BUT_B)
        keyb_cancel();        
#endif
    break;
    case DISPLAY_DEBUG:
      if(cinput == BUT_MENU)
        set_display_page(DISPLAY_MAIN);
    break;
  }

  audio_service();
  battery_level_service();
  display_service();
  led_service();
  input_service();
  uart_handler_service();
  GO.update();
  heart_beat();
}
