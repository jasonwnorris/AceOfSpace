// Sound.hpp

#ifndef __SOUND_HPP__
#define __SOUND_HPP__

// SDL Includes
#include <SDL.h>
#include <SDL_mixer.h>
// STL Includes
#include <fstream>
#include <string>
#include <map>

class Sound
{
  public:
    Sound(const std::string& p_Filename, bool p_IsLoop);
    ~Sound();

    static std::map<std::string, Sound*> SoundList;

    static void LoadSounds();
    static void UnloadSounds();

    static void PlaySound(const std::string& p_Keyname);

    Mix_Music* m_MixMusic;
    bool m_IsLoop;
};

#endif
