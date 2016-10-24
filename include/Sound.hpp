// Sound.hpp

#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include <SDL.h>
#include <SDL_mixer.h>

#include <fstream>
#include <string>
#include <map>

class Sound
{
  public:
    Sound(std::string filename, bool loop);
    ~Sound();

    static std::map<std::string, Sound*> SoundList;

    static void LoadSounds();
    static void UnloadSounds();

    static void PlaySound(std::string keyname);

    Mix_Music* mixMusic;
    bool loop;
};

#endif
