// Sound.cpp //
#include "Sound.hpp"

std::map<std::string, Sound*> Sound::SoundList;

Sound::Sound(std::string filename, bool loop)
{
  std::string filepath = "resources/" + filename;

  this->mixMusic = Mix_LoadMUS(filepath.c_str());
  this->loop = loop;
}

Sound::~Sound()
{
  Mix_FreeMusic(mixMusic);
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
    SDL_Log("Loaded sound: %s\n", keyname.c_str());
  }

  file.close();
}

void Sound::UnloadSounds()
{
  for (std::map<std::string, Sound*>::iterator Iter = SoundList.begin(); Iter != SoundList.end(); ++Iter)
  {
    SDL_Log("Deleting sound: %s\n", (*Iter).first.c_str());
    delete (*Iter).second;
  }

  SoundList.clear();
}

void Sound::PlaySound(std::string keyname)
{
  Sound* sound = SoundList[keyname];

  if (sound->loop)
  {
    Mix_PlayMusic(sound->mixMusic, -1);
  }
  else
  {
    Mix_PlayMusic(sound->mixMusic, 0);
  }
}
