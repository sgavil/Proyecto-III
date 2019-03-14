#include "AudioSource.h"
//Constructora, le llegan los parametros del mundo que afecta a cualquier entidad con sonido 3D
AudioSource::AudioSource(float doppler, float rolloff) : doppler_(doppler), rolloff_(rolloff)
{
	result_ = FMOD::System_Create(&system_);
	FMOD_OK_ERROR_CHECK();
	result_ = system_->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	FMOD_OK_ERROR_CHECK();
	system_->set3DSettings(doppler_, 1.0, rolloff_);
}

AudioSource::~AudioSource()
{
	result_ = system_->release();
	FMOD_OK_ERROR_CHECK();
}

void AudioSource::FMOD_OK_ERROR_CHECK()
{
	if (result_ != FMOD_OK)
	{
		std::cout << "FMOD error!" << result_ << FMOD_ErrorString(result_);
		exit(-1);
	}
}

void AudioSource::ADD_2D_SOUND(std::string fileName, int loopCount, float volume, float pan)
{
	FMOD::Sound* snd;
	FMOD_CREATESOUNDEXINFO* ErrInf = 0;

	if(loopCount < 0)
	result_ = system_->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, ErrInf, &snd);
	else result_ = system_->createSound(fileName.c_str(), FMOD_DEFAULT, ErrInf, &snd);

	FMOD_OK_ERROR_CHECK();

	soundValues aux;
	aux.loopCount = loopCount; aux.pan = pan; aux.volume = volume; aux.snd = snd;

	soundList_.insert(std::make_pair(fileName, aux));
}

void AudioSource::ADD_3D_SOUND(std::string fileName, int loopCount, float volume)
{
	FMOD::Sound* snd;
	FMOD_CREATESOUNDEXINFO* ErrInf = 0;

	if (loopCount < 0)
		result_ = system_->createSound(fileName.c_str(), FMOD_3D | FMOD_LOOP_NORMAL, ErrInf, &snd);
	else result_ = system_->createSound(fileName.c_str(), FMOD_3D | FMOD_DEFAULT, ErrInf, &snd);

	FMOD_OK_ERROR_CHECK();

	soundValues3D aux;
	aux.loopCount = loopCount; aux.volume = volume; aux.snd = snd;

	soundList3D_.insert(std::make_pair(fileName, aux));
}

void AudioSource::PLAY_2D_SOUND(std::string AudioID)
{
	FMOD::Channel* chn;
	auto it = soundList_.find(AudioID);
	result_ = system_->playSound((*it).second.snd, 0, false, &chn);

	chn->setVolume((*it).second.volume);
	chn->setPan((*it).second.pan);
	chn->setLoopCount((*it).second.loopCount);

	FMOD_OK_ERROR_CHECK();
}

void AudioSource::PLAY_3D_SOUND(std::string AudioID, float posX, float posY, float posZ)
{
	FMOD::Channel* chn;
	auto it = soundList3D_.find(AudioID);
	result_ = system_->playSound((*it).second.snd, 0, true, &chn);
	(*it).second.emitter.x = &posX; (*it).second.emitter.y = &posY; (*it).second.emitter.y = &posY;
	(*it).second.vel = { 0,0,0 };

	FMOD_VECTOR pos = { posX, posY, posZ };

	chn->setVolume((*it).second.volume);
	chn->setLoopCount((*it).second.loopCount);
	chn->set3DAttributes(&pos, &(*it).second.vel);

	FMOD_OK_ERROR_CHECK();
}

void AudioSource::set3DFactors(float doppler, float rolloff)
{
	doppler_ = doppler;
	rolloff_ = rolloff;
	system_->set3DSettings(doppler_, 1.0, rolloff_);
}
