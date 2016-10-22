// Timer.cpp //
#include "Timer.hpp"

Timer::Timer()
{
   previousTime = 0.0f;
}

Timer::~Timer()
{
}

// gets time since SDL was initialized (milliseconds)
float Timer::getStartTime()
{
   return SDL_GetTicks() / 1000.0f;
}

// gets time from last time this was called (milliseconds)
float Timer::getDeltaTime()
{
   float thisTime = getStartTime();
   float deltaTime = thisTime - previousTime;
   previousTime = thisTime;

   return deltaTime;
}
