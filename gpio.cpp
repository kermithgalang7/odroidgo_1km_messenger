#include <odroid_go.h>

#include "gpio.h"

int display_keyboard_now = 1;
int led_stat = 0;
int led_brightness = 0;
int led_counter = 0;
int led_dimming = 0;

int current_key = BUT_NONE;
int direction_button = 0x00;
int menu_button = 0x00;
int action_button = 0x00;


void output_init(void)
{
  pinMode(PIN_BLUE_LED, OUTPUT);
  digitalWrite(PIN_BLUE_LED, HIGH);
  set_led_stat(LED_STAT_BEATING);
}
void input_init(void)
{
  
}
int consume_input(void)
{
  int ret_val;

  ret_val = current_key;
  current_key = BUT_NONE;
  return ret_val;  
}
void input_service(void)
{
#if 1
  if (GO.BtnA.isPressed() == 1)
    action_button |= BUT_MARK_A;
  else if(GO.BtnA.isPressed() == 0)
  {
    if((action_button & BUT_MARK_A) != 0)
    {
      current_key = BUT_A;
      action_button = action_button & !BUT_MARK_A;
    }
  }
  if (GO.BtnB.isPressed() == 1)
    action_button |= BUT_MARK_B;
  else if(GO.BtnB.isPressed() == 0)
  {
    if((action_button & BUT_MARK_B) != 0)
    {
      current_key = BUT_B;
      action_button = action_button & !BUT_MARK_B;
    }
  }
    
  if (GO.BtnStart.isPressed() == 1)
    menu_button |= BUT_MARK_START;
  else if(GO.BtnStart.isPressed() == 0)
  {
    if((menu_button & BUT_MARK_START) != 0)
    {
      current_key = BUT_START;
      menu_button = menu_button & !BUT_MARK_START;
    }
  }
  if (GO.BtnSelect.isPressed() == 1)
    menu_button |= BUT_MARK_SEL;
  else if(GO.BtnSelect.isPressed() == 0)
  {
    if((menu_button & BUT_MARK_SEL) != 0)
    {
      current_key = BUT_SEL;
      menu_button = menu_button & !BUT_MARK_SEL;
    }
  }    
  if (GO.BtnVolume.isPressed() == 1)
    menu_button |= BUT_MARK_VOL;
  else if(GO.BtnVolume.isPressed() == 0)
  {
    if((menu_button & BUT_MARK_VOL) != 0)
    {
      current_key = BUT_VOL;
      menu_button = menu_button & !BUT_MARK_VOL;
    }
  }    
  if (GO.BtnMenu.isPressed() == 1)
    menu_button |= BUT_MARK_MENU;
  else if(GO.BtnMenu.isPressed() == 0)
  {
    if((menu_button & BUT_MARK_MENU) != 0)
    {
      current_key = BUT_MENU;
      menu_button = menu_button & !BUT_MARK_MENU;
    }
  }    
#endif
  if (GO.JOY_X.isAxisPressed() == 1)
    direction_button |= BUT_MARK_RIGHT;  
  else if(GO.JOY_X.isAxisPressed() == 0)
  {
    if((direction_button & BUT_MARK_RIGHT) != 0)
    {
      current_key = BUT_RIGHT;
      direction_button = direction_button & !BUT_MARK_RIGHT;
    }
  }
  if (GO.JOY_X.isAxisPressed() == 2)
    direction_button |= BUT_MARK_LEFT;
  else if(GO.JOY_X.isAxisPressed() == 0)
  {
    if((direction_button & BUT_MARK_LEFT) != 0)
    {
      current_key = BUT_LEFT;
      direction_button = direction_button & !BUT_MARK_LEFT;
    }
  }
  if (GO.JOY_Y.isAxisPressed() == 1)
    direction_button |= BUT_MARK_DOWN;
  else if(GO.JOY_Y.isAxisPressed() == 0)
  {
    if((direction_button & BUT_MARK_DOWN) != 0)
    {
      current_key = BUT_DOWN;
      direction_button = direction_button & !BUT_MARK_DOWN;
    }
  }
  if (GO.JOY_Y.isAxisPressed() == 2)
    direction_button |= BUT_MARK_UP;  
  else if(GO.JOY_Y.isAxisPressed() == 0)
  {
    if((direction_button & BUT_MARK_UP) != 0)
    {
      current_key = BUT_UP;
      direction_button = direction_button & !BUT_MARK_UP;
    }
  }

  GO.lcd.setTextSize(1);
  GO.lcd.setTextColor(GREEN, BLACK);
  GO.lcd.setCursor(280, 20);
  GO.lcd.print(direction_button);
  GO.lcd.print("  ");
  GO.lcd.setCursor(280, 30);
  GO.lcd.print(menu_button);
  GO.lcd.print("  ");
  GO.lcd.setCursor(280, 40);
  GO.lcd.print(action_button);
  GO.lcd.print("  ");
}

void set_led_stat(int stat)
{
  led_stat = stat;
  if(stat == LED_STAT_BEATING)
  {
    ledcAttachPin(PIN_BLUE_LED, PWM_CHANNEL); 
    ledcSetup(PWM_CHANNEL, PWM_12KHZ, PWM_8BIT);
  }
  else
  {
    ledcDetachPin(PIN_BLUE_LED);
    pinMode(PIN_BLUE_LED, OUTPUT);
  }
  led_counter = 0;
}
int led_service(void)
{
  switch(led_stat)
  {
    case LED_STAT_ON:
      digitalWrite(PIN_BLUE_LED, HIGH);
    break;
    case LED_STAT_OFF:
      digitalWrite(PIN_BLUE_LED, LOW);
    break;
    case LED_STAT_FASTBLINK:  
      if(led_counter == 25)
        digitalWrite(PIN_BLUE_LED, HIGH);
      else if(led_counter == 50)
      {
        digitalWrite(PIN_BLUE_LED, LOW);
        led_counter = 0;
      }
    break;
    case LED_STAT_SLOWBLINK:  
      if(led_counter == 100)
        digitalWrite(PIN_BLUE_LED, HIGH);
      else if(led_counter == 200)
      {
        digitalWrite(PIN_BLUE_LED, LOW);
        led_counter = 0;
      }
    break;
    case LED_STAT_BEATING:    
      if(led_counter == 1)
      {
        if(led_dimming == 0)
          led_brightness++;
        else
          led_brightness--;
        if(led_brightness >= 255)
          led_dimming = 1;
        else if(led_brightness <= 0)
          led_dimming = 0;
        
        ledcWrite(PWM_CHANNEL, led_brightness);
        led_counter = 0;
      }
    break;
    default:
    ;
  }

  #if 0
  String test11 = String(" ") + led_brightness + " ";
  GO.lcd.setCursor(100, 100);
  GO.lcd.setTextSize(1);
  GO.lcd.setTextColor(YELLOW, BLACK);   
  GO.lcd.print(test11);  
  #endif  

  if(led_counter <= 255)
    led_counter++;
  else
    led_counter = 0;
  return 0;  
}
