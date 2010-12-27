  /* See audio.h */
#include "../include/audio.h"

Audio::Audio()
{
	
}

int Audio::Init()
{
	// Opens a sound device
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    return -1;
	}
	
	cout<<"Audio device initialized."<<"\n";
	
	return 1;
}

// Loads a sound
int Audio::LoadSound(int type, string filename)
{
	// load the MP3 file "music.mp3" to play as music
	Mix_Music* temp_sound=Mix_LoadMUS(filename.c_str());
	if(!temp_sound) {
		cout<<"Mix_LoadMUS "<<filename<<" Mix_GetError()";
  	// this might be a critical error...
  	return -1;
	}
	
	sound.push_back(temp_sound);
	cout<<"File '"<<filename<<"' loaded succesfully.\n";
	
	return 1;
}
		
//Starting a sound
int Audio::StartSound(int n)
{
	if(Mix_PlayMusic(sound[n], 1)==-1) {
    printf("Mix_PlayMusic: %s\n", Mix_GetError());
    // well, there's no music!
    return -1;
		}
	cout<<"Playing sound '"<<n<<"'\n";
		
	return 1;
}

// Pausing playing
int Audio::PauseSound(int n)
{
	
}

// Seeking
void Audio::Seek(int time)
{
	
}

// Get current moment of playing in milliseconds
int Audio::GetLocation()
{
	
}

Audio::~Audio()
{
	Mix_CloseAudio();
}
