// Sound.h //
#ifndef SOUND_H
#define SOUND_H

#include "SDL.h"
#include "SDL_mixer.h"

#include <fstream>
#include <string>
#include <map>
using namespace std;

class Sound
{
	public:
		Sound(string filename, bool loop);
		~Sound();

		static map<string,Sound*> SoundList;

		static void LoadSounds();
		static void UnloadSounds();
		
		static void PlaySound(string keyname);
		
		Mix_Music* mixMusic;
        bool loop;
};

#endif
