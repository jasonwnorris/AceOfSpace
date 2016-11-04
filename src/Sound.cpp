// Sound.cpp

// AOS Includes
#include "Config.hpp"
#include "Sound.hpp"

std::map<std::string, Sound*> Sound::SoundList;

Sound::Sound(const std::string& p_Filename, bool p_IsLoop)
{
  std::string filepath = c_ResourcesPath + p_Filename;

  m_MixMusic = Mix_LoadMUS(filepath.c_str());
  m_IsLoop = p_IsLoop;
}

Sound::~Sound()
{
  Mix_FreeMusic(m_MixMusic);
}

bool Sound::LoadSounds()
{
  std::ifstream file(c_SoundsFilename, std::ios_base::in);
  if (!file.is_open())
  {
    SDL_Log("Failed to open file: %s", c_SoundsFilename.c_str());
    return false;
  }

  std::string keyname = "";
  std::string filename = "";
  std::string loops = "";

  getline(file, keyname);

  while (!file.eof())
  {
    file >> keyname >> filename >> loops;

    Sound* sound = new Sound(filename, (loops == "yes"));
    if (sound != nullptr)
    {
      SDL_Log("Loaded sound: %s", keyname.c_str());
      SoundList[keyname] = sound;
    }
    else
    {
      SDL_Log("Failed to load sound: %s", keyname.c_str());
      return false;
    }
  }

  file.close();

  return true;
}

void Sound::UnloadSounds()
{
  for (auto& pair : SoundList)
  {
    SDL_Log("Unloading sound: %s", pair.first.c_str());
    delete pair.second;
  }

  SoundList.clear();
}

void Sound::PlaySound(const std::string& p_Keyname)
{
  Sound* sound = SoundList[p_Keyname];
  if (sound != nullptr)
  {
    Mix_PlayMusic(sound->m_MixMusic, sound->m_IsLoop ? -1 : 0);
  }
}
