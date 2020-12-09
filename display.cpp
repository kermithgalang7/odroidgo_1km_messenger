#include <odroid_go.h>

#include "display.h"

int current_display;
String messages[MAX_LINEMESSAGE];
char edit_text[100];

extern int display_keyboard_now;

void push_message_queue(String msg)
{
  #if 0
  for(int i = 0; i < MAX_LINEMESSAGE; i++)
  {
    messages[i - MAX_LINEMESSAGE - 1] = messages[i - MAX_LINEMESSAGE - 2];
  }
  #endif
  messages[0] = msg;
}

int compose_edit_text_bar(void)
{
  GO.lcd.setCursor(0, 0);
  GO.lcd.setTextSize(2);
  GO.lcd.setTextColor(YELLOW, BLACK);   
  GO.lcd.print("ME: ");    
}
int compose_message_area(int number_of_lines)
{ 
  GO.lcd.setCursor(0, 20);
  GO.lcd.setTextColor(YELLOW, BLACK); 

  if(number_of_lines > MAX_LINEMESSAGE)
    number_of_lines = MAX_LINEMESSAGE;
  for(int i = 0; i < number_of_lines; i++)
  {    
    if(i<3)
      GO.lcd.setTextSize(2);
    else
      GO.lcd.setTextSize(1);
      
    GO.lcd.print("[");    
    GO.lcd.print(messages[i]);
    GO.lcd.println("]");
  }
  
  return 0;
}
int compose_keyboard(void)
{
  GO.lcd.setTextSize(2);
  GO.lcd.setTextColor(RED, BLACK);
  GO.lcd.setCursor(20, 150);
  GO.lcd.print("QWERTYUIOP[]");
  GO.lcd.setCursor(20, 170);
  GO.lcd.print("ASDFGHJKL;'\\");  
  GO.lcd.setCursor(20, 190);
  GO.lcd.print("ZXCVBNM,./");
  return 0;
}
int display_message_screen(void)
{
  if(display_keyboard_now == 1)
  {
    compose_edit_text_bar();
    compose_keyboard();
    compose_message_area(10);
  }
  else
  {
    compose_message_area(MAX_LINEMESSAGE);  
  }

  return 0;
}

void display_init(void)
{
  GO.lcd.clearDisplay();  
  current_display = DISPLAY_BLANK; 
}

int set_display_page(int disp_page)
{
  GO.lcd.clearDisplay();  
  current_display = disp_page;
  return 0;
}
int get_display_page(void)
{
  return current_display;
}
void open_menu(int display)
{
  current_display = display; 
}

int display_service(void)
{
  switch(current_display)
  {
    case DISPLAY_BLANK:
      GO.lcd.setTextSize(1);
      GO.lcd.setTextColor(GREEN, BLACK);
      GO.lcd.setCursor(0, 0);
      GO.lcd.print("Developed by IOTLaunchPad");
    break;
    case DISPLAY_SPLASH:
      GO.lcd.setTextSize(3);
      GO.lcd.setTextColor(GREEN, BLACK);
      GO.lcd.setCursor(50, 55);
      GO.lcd.print("IOTLaunchPad");
      GO.lcd.setCursor(80, 85);
      GO.lcd.print("Messenger");
    break;
    case DISPLAY_MAIN:
      display_message_screen();
    break;
    default:
      GO.lcd.setTextSize(1);
      GO.lcd.setTextColor(GREEN, BLACK);
      GO.lcd.setCursor(0, 0);
      GO.lcd.print("Invalid Page");
  }
  
  
  return 0;
}
  
