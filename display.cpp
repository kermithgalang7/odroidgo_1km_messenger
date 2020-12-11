#include <odroid_go.h>

#include "display.h"
#include "battery.h"

int current_display;
char current_message[50] = "test";
int current_m_index = 0;
String messages[MAX_LINEMESSAGE];
char edit_text[100];

int current_x = 0;
int current_y = 0;
char keyb1[15] = "QWERTYUIOP[]  ";
char keyb2[15] = "ASDFGHJKL;'\\ ";  
char keyb3[15] = "ZXCVBNM,./    ";

extern int display_keyboard_now;

void push_message_queue(String msg)
{
  GO.lcd.clearDisplay();  
  #if 1
  for(int i = 0; i < MAX_LINEMESSAGE; i++)
  {
    messages[MAX_LINEMESSAGE - i - 1] = messages[MAX_LINEMESSAGE - i - 2];
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
  GO.lcd.print(current_message);
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

  GO.lcd.setTextSize(1);
  GO.lcd.setTextColor(GREEN, BLACK);
  GO.lcd.setCursor(280, 60);
  GO.lcd.print(current_x);
  GO.lcd.setCursor(300, 60);
  GO.lcd.print(current_y);
  
  return 0;
}
void keyb_left(void)
{
  if(current_x > 0)
    current_x--;
}
void keyb_right(void)
{
  if(current_x < (MAX_KEYX - 1))
    current_x++;  
}
void keyb_up(void)
{
  if(current_y > 0)
    current_y--;  
}
void keyb_down(void)
{
  if(current_y < (MAX_KEYY - 1))
    current_y++;  
}
void keyb_ok(void)
{
  if(current_y == 0)
    current_message[current_m_index] = keyb1[current_x];
  if(current_y == 1)
    current_message[current_m_index] = keyb2[current_x];
  if(current_y == 2)
    current_message[current_m_index] = keyb3[current_x];
  current_m_index++;
}
void keyb_cancel(void)
{  
  if(current_m_index > 0)
    current_m_index--;
  current_message[current_m_index] = ' ';    
}
int compose_keyboard(void)
{  
  for(int i = 0; i < MAX_KEYY; i++)
  {
    for(int j = 0; j < MAX_KEYX; j++)
    { 
      if((current_x == j) && (current_y == i))
      {
        GO.lcd.setTextSize(2);
        GO.lcd.setTextColor(YELLOW, BLUE);  
      }
      else
      {
        GO.lcd.setTextSize(2);
        GO.lcd.setTextColor(RED, BLACK);  
      }
      GO.lcd.setCursor((20 * j) + 20, (20 * i) + 180);
      switch(i)
      {
        case 0: 
          GO.lcd.print(keyb1[j]);
        break;
        case 1: 
          GO.lcd.print(keyb2[j]);
        break;
        case 2: 
          GO.lcd.print(keyb3[j]);
        break;
      }
    }
  }
//  GO.lcd.print("QWERTYUIOP[]");
//  GO.lcd.setCursor(20, 170);
//  GO.lcd.print("ASDFGHJKL;'\\");  
//  GO.lcd.setCursor(20, 190);
//  GO.lcd.print("ZXCVBNM,./");
  return 0;
}

int compose_battery_indicator(void)
{
  double batt = get_battery_level();
//  double batt = 3.6;

  if(batt > 4.0)
    GO.lcd.setTextColor(GREEN, BLACK);
  else if(batt > 3.7)
    GO.lcd.setTextColor(YELLOW, BLACK);
  else
    GO.lcd.setTextColor(RED, BLACK);
  GO.lcd.setTextSize(1);  
  GO.lcd.setCursor(280, 0);
  GO.lcd.print(batt);
  GO.lcd.print(" V");
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
  compose_battery_indicator();

  return 0;
}

int display_debug_screen(void)
{
  GO.lcd.setTextSize(1);
  GO.lcd.setCursor(0, 0);
  GO.lcd.setTextColor(GREEN, BLACK);
  GO.lcd.println("/* Direction pad */");
  GO.lcd.printf("Joy-Y-Up: %s \n", (GO.JOY_Y.isAxisPressed() == 2) ? "X" : " ");
  GO.lcd.printf("Joy-Y-Down: %s \n", (GO.JOY_Y.isAxisPressed() == 1) ? "X" : " ");
  GO.lcd.printf("Joy-X-Left: %s \n", (GO.JOY_X.isAxisPressed() == 2) ? "X" : " ");
  GO.lcd.printf("Joy-X-Right: %s \n", (GO.JOY_X.isAxisPressed() == 1) ? "X" : " ");
  GO.lcd.println("");
  GO.lcd.println("/* Function key */");
//  GO.lcd.printf("Menu: %s \n", (GO.BtnMenu.isPressed() == 1) ? "X" : " ");
  GO.lcd.printf("Volume: %s \n", (GO.BtnVolume.isPressed() == 1) ? "X" : " ");
  GO.lcd.printf("Select: %s \n", (GO.BtnSelect.isPressed() == 1) ? "X" : " ");
  GO.lcd.printf("Start: %s \n", (GO.BtnStart.isPressed() == 1) ? "X" : " ");
  GO.lcd.println("");
  GO.lcd.println("/* Actions */");
  GO.lcd.printf("B: %s \n", (GO.BtnB.isPressed() == 1) ? "X" : " ");
  GO.lcd.printf("A: %s \n", (GO.BtnA.isPressed() == 1) ? "X" : " ");
  GO.lcd.println("");
  GO.lcd.printf("Voltage: %1.3lf V\n", get_battery_level());
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
    case DISPLAY_DEBUG:
      display_debug_screen();
    break;
    default:
      GO.lcd.setTextSize(1);
      GO.lcd.setTextColor(GREEN, BLACK);
      GO.lcd.setCursor(0, 0);
      GO.lcd.print("Invalid Page");
  }
  
  return 0;
}
  
