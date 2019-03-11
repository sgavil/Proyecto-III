#include "AudioSource.h"

AudioSource::AudioSource()
{
	result_ = FMOD::System_Create(&system_);
	FMOD_OK_ERROR_CHECK();
	result_ = system_->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	FMOD_OK_ERROR_CHECK();
}

AudioSource::~AudioSource()
{
	&FMOD::System::release;
}

void AudioSource::FMOD_OK_ERROR_CHECK()
{
	if (result_ != FMOD_OK)
	{
		std::cout << "FMOD error!" << result_ << FMOD_ErrorString(result_);
		exit(-1);
	}
}

void AudioSource::ADD_SOUND(std::string fileName)
{
	FMOD_CREATESOUNDEXINFO* ErrInf;

}

void AudioSource::PLAY_SOUND()
{
}
