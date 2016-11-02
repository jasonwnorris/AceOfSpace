// Timer.hpp

#ifndef __TIMER_HPP__
#define __TIMER_HPP__

// SDL Includes
#include <SDL.h>

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
