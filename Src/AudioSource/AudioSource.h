#pragma once
#include <iostream>
#include <string>
#include <map>

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

class AudioSource 
{

	std::map<std::string, FMOD::Sound*> soundList_;

public:
	AudioSource();
	~AudioSource();

	
	void ADD_SOUND(std::string fileName);
	void PLAY_SOUND(std::string AudioID);

private:
	void FMOD_OK_ERROR_CHECK();
	
	FMOD_RESULT result_;
	FMOD::System* system_;

};