// Star.hpp

#ifndef __STAR_HPP__
#define __STAR_HPP__

// AOS Includes
#include "Object.hpp"

class Star : public Object
{
  public:
    Star(const std::string& p_Keyname);

    void Update(float p_DeltaTime);
};

#endif
