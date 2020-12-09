#include <odroid_go.h>
#include <WiFi.h>

#include "audio.h"
#include "battery.h"
#include "display.h"
#include "gpio.h"
#include "wifi.h"

#define HW_SERIAL_TX    15

HardwareSerial serial1(1);

int program_flow = 0;

void hardware_init(void)
{
  display_init();  
  
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

  serial1.begin(9600, SERIAL_8N1, 15, 4);

  hardware_init();
}

String testmsg = "";
char carray[100];
char c;
int i = 0;
int cdisplay;
void loop() {
  // put your main code here, to run repeatedly:

//  serial1.println("kermith ");
  if(serial1.available())
  {    
    c = serial1.read();
    if(c != '\r')
    {
      carray[i] = c;
      i++;
    }    
    else
      push_message_queue(testmsg);
  }
    
  
  cdisplay = get_display_page();
  switch(cdisplay)
  {
    case DISPLAY_BLANK:
      if(program_flow == 100)
      {
        program_flow = 0;
        set_display_page(DISPLAY_SPLASH);
      }
    break;
    case DISPLAY_SPLASH:
      if(program_flow == 500)
      {
        program_flow = 0;
        set_display_page(DISPLAY_MAIN);
      }
    break;
  }

  display_service();
  GO.update();
  heart_beat();
}
