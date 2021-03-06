#include <string.h>

#include "audio.h"
#include "uart_handler.h"
#include "display.h"

HardwareSerial softserial(1);
char carray[100];
int i = 0;

void uart_handler_init(void)
{
  softserial.begin(9600, SERIAL_8N1, SW_SERIAL_TX, SW_SERIAL_RX);
}

int send_uart_message(char* msg)
{
  softserial.println(msg);
  return 0;
}
int uart_handler_service(void)
{
  String testmsg = "";  
  char c;    
  
//  softserial.println("kermith ");
  if(softserial.available())
  {    
    c = softserial.read();
    if(c != '\r')
    {
      carray[i] = c;
      i++;
    }    
    else
    {
      testmsg = carray;
      push_message_queue(testmsg);
      enable_1sec_interval();
      memset(carray, 0, 100);
      i = 0;
    }
  }
  
  return 0;
}
