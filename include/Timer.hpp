// Timer.h //
#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

class Timer
{
  public:
     Timer();
     ~Timer();

     float getStartTime();
     float getDeltaTime();

  private:
     float previousTime;
};

#endif
