#ifndef __UART_HANDLER_H__
#define __UART_HANDLER_H__

#define SW_SERIAL_TX    15
#define SW_SERIAL_RX    4

void uart_handler_init(void);
int send_uart_message(char* msg);
int uart_handler_service(void);


#endif //__UART_HANDLER_H__
