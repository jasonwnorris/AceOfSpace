// Sound.cpp

// AOS Includes
#include "Sound.hpp"

std::map<std::string, Sound*> Sound::SoundList;

Sound::Sound(const std::string& p_Filename, bool p_IsLoop)
{
  std::string filepath = "resources/" + p_Filename;

  this->m_MixMusic = Mix_LoadMUS(filepath.c_str());
  this->m_IsLoop = p_IsLoop;
}

Sound::~Sound()
{
  Mix_FreeMusic(m_MixMusic);
}

void Sound::LoadSounds()
{
  std::ifstream file;

  file.open("resources/sounds.txt");

  std::string keyname = "";
  std::string filename = "";
  std::string loops = "";

  getline(file, keyname);

  while (!file.eof())
  {
    file >> keyname;
    file >> filename;
    file >> loops;

    SoundList[keyname] = new Sound(filename, (loops == "yes"));

    SDL_Log("Loaded sound: %s", keyname.c_str());
  }

  file.close();
}

void Sound::UnloadSounds()
{
  for (std::map<std::string, Sound*>::iterator Iter = SoundList.begin(); Iter != SoundList.end(); ++Iter)
  {
    SDL_Log("Deleting sound: %s", (*Iter).first.c_str());
    delete (*Iter).second;
  }

  SoundList.clear();
}

void Sound::PlaySound(const std::string& p_Keyname)
{
  Sound* sound = SoundList[p_Keyname];

  Mix_PlayMusic(sound->m_MixMusic, sound->m_IsLoop ? -1 : 0);
}
