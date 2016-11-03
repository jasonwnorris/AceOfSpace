// Timer.cpp

// AOS Includes
#include "Timer.hpp"

Timer::Timer()
{
   m_PreviousTime = 0.0f;
}

Timer::~Timer()
{
}

float Timer::GetStartTime()
{
   return SDL_GetTicks() / 1000.0f;
}

float Timer::GetDeltaTime()
{
   float currentTime = GetStartTime();
   float deltaTime = currentTime - m_PreviousTime;
   m_PreviousTime = currentTime;

   return deltaTime;
}
