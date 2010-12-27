/* The audio class.*/

/*
Holds all methods relating to audio and returning data out of the currently playing music,
and handles sound effects and so on.
*/

#ifndef AUDIO_H_
#define AUDIO_H_

#include "../include/main.h"

class Audio {
	private:
		// Prime track to play.
		vector < Mix_Music *> sound;
		
		// Whether music is playing or paused
		bool playing;
		// Whether music is started
		bool started;
		
		//Enum names for sound types
		enum MyEnumType {MUSIC, EFFECT};
		
	public:
		Audio();
		~Audio();
		
		// Initializing audio device
		int Init();
		
		// Loading sounds
		/*type = type of sound, either EFFECT or MUSIC
			filename = surprisingly, the name of sound to be loaded
		*/
		int LoadSound(int type, string filename);
		
		//Starting a sound
		/*
			n = number of sound to play.
		*/
		int StartSound(int n);
		
		// Pausing playing
		/*
			n = number of sound to pause.
		*/
		int PauseSound(int n);
		
		// Seeking
		void Seek(int time);
		
		// Getting the time where audio is
		int GetLocation();
};

#endif
