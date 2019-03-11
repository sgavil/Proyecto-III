#include <iostream>
#include <string>

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

class AudioSource 
{
	AudioSource();
	~AudioSource();

	void FMOD_OK_ERROR_CHECK();
	void ADD_SOUND(std::string fileName);
	void PLAY_SOUND();
	
	FMOD_RESULT result_;
	FMOD::System* system_;
	FMOD::Sound* snd;

};
