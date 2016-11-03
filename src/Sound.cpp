// Sound.cpp

// AOS Includes
#include "Sound.hpp"

std::map<std::string, Sound*> Sound::SoundList;

Sound::Sound(const std::string& filename, bool loop)
{
  std::string filepath = "resources/" + filename;

  this->m_MixMusic = Mix_LoadMUS(filepath.c_str());
  this->m_IsLoop = loop;
}

Sound::~Sound()
{
  Mix_FreeMusic(m_MixMusic);
}

// load in sound files from text document
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

    Sound* sound;

    if (loops == "yes")
    {
      sound = new Sound(filename, true);
    }
    else
    {
      sound = new Sound(filename, false);
    }

    SoundList[keyname] = sound;
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

void Sound::PlaySound(const std::string& keyname)
{
  Sound* sound = SoundList[keyname];

  if (sound->m_IsLoop)
  {
    Mix_PlayMusic(sound->m_MixMusic, -1);
  }
  else
  {
    Mix_PlayMusic(sound->m_MixMusic, 0);
  }
}
