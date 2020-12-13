#ifndef __AUDIO_H__
#define __AUDIO_H__


void audio_init(void);
int run_tone(int millisec);
int run_beep(int millisec);

int enable_1sec_interval(void);
int disable_1sec_interval(void);
int enable_5sec_interval(void);
int disable_5sec_interval(void);
int disable_interval(void);

int audio_service(void);

#endif //__AUDIO_H__
