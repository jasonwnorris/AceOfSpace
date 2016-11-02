// Star.hpp

#ifndef __STAR_HPP__
#define __STAR_HPP__

// AOS Includes
#include "Object.hpp"

class Star : public Object
{
  public:
    Star(std::string keyname);

    void Update(float deltaTime);
};

#endif
