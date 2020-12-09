#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define DISPLAY_BLANK       0
#define DISPLAY_SPLASH      1
#define DISPLAY_DEBUG       2
#define DISPLAY_MAIN        3
#define DISPLAY_MENU        4
#define DISPLAY_BTMENU      5
#define DISPLAY_WIFIMENU    6
#define DISPLAY_WIFIAPMENU  7
#define DISPLAY_CUSTOM      8
#define DISPLAY_GPIO        9
#define DISPLAY_ABOUT       90
#define DISPLAY_TEST        99

#define MAX_LINEMESSAGE     15


void push_message_queue(String msg);
void display_init(void);
int set_display_page(int disp_page);
int get_display_page(void);
void open_menu(int display);
int display_service(void);

#endif //__DISPLAY_H__
