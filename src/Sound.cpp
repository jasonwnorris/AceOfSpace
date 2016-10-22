// Sound.cpp //
#include "Sound.h"

map<string,Sound*> Sound::SoundList;

Sound::Sound(string filename, bool loop)
{
	string filepath = "resources/" + filename;
	
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
	ifstream file;

    file.open("resources/sounds.txt");

    string keyname = "";
    string filename = "";
	string loops = "";

	getline(file, keyname);

	while(!file.eof())
    {
		file >> keyname;
		file >> filename;
		file >> loops;
		
		Sound* sound;

		if(loops == "yes")
		    sound = new Sound(filename, true);
		else
		    sound = new Sound(filename, false);
		    
		SoundList[keyname] = sound;
		printf("Loaded sound: %s\n", keyname.c_str());
	}

    file.close();
}

void Sound::UnloadSounds()
{
   for(map<string,Sound*>::iterator Iter = SoundList.begin(); Iter != SoundList.end(); ++Iter)
   {
      printf("Deleting sound: %s\n", (*Iter).first.c_str());
      delete (*Iter).second;
   }

   SoundList.clear();
}

void Sound::PlaySound(string keyname)
{
	Sound* sound = SoundList[keyname];
	
	if(sound->loop)
		Mix_PlayMusic(sound->mixMusic, -1);
	else
		Mix_PlayMusic(sound->mixMusic, 0);
}
