#include <odroid_go.h>

#include "audio.h"

int audio_counter = 0;
int interval_1sec = 0;
int interval_5sec = 0;

void audio_init(void)
{
//  GO.Speaker.beep();  
  GO.Speaker.tone(3000,200);
}

int run_tone(int millisec)
{
  GO.Speaker.tone(8000,millisec);
  return 0;
}

int run_beep(int millisec)
{
//  for(int i; i < millisec; i++)
//  {
//    GO.Speaker.beep();
//  }
  return 0;
}

int enable_1sec_interval(void)
{
  interval_1sec = 1;
  audio_counter = 0;
  GO.Speaker.beep();
  return 0;
}
int disable_1sec_interval(void)
{
  interval_1sec = 0;
  return 0;
}

int enable_5sec_interval(void)
{
  interval_5sec = 1;
  audio_counter = 0;
  GO.Speaker.beep();
  return 0;
}
int disable_5sec_interval(void)
{
  interval_5sec = 0;
  return 0;
}
int disable_interval(void)
{
  interval_1sec = 0;
  interval_5sec = 0;
  audio_counter = 0;
}

int audio_service(void)
{
  if(interval_1sec == 1)
  {
    if(audio_counter == 250)
    {
      GO.Speaker.beep();
      audio_counter = 0;
    }
  }

  if(audio_counter < 10000)
    audio_counter++;
  else
    audio_counter = 0;
  return 0;
}
