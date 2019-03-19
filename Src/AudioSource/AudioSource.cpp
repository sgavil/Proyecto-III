#include "AudioSource.h"


std::unique_ptr<AudioSource> AudioSource::instance_;

AudioSource * AudioSource::instance(float doppler, float rolloff)
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_.get() == nullptr)
		instance_.reset(new AudioSource(doppler, rolloff));

	return instance_.get();
}


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

void AudioSource::ADD_2D_SOUND(std::string fileName, std::string id, int loopCount, float volume, float pan)
{
	FMOD::Sound* snd;
	FMOD_CREATESOUNDEXINFO* ErrInf = 0;

	if(loopCount < 0)
	result_ = system_->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, ErrInf, &snd);
	else result_ = system_->createSound(fileName.c_str(), FMOD_DEFAULT, ErrInf, &snd);

	FMOD_OK_ERROR_CHECK();

	soundValues aux;
	aux.loopCount = loopCount; aux.pan = pan; aux.volume = volume; aux.snd = snd, aux.id_ = id;

	soundList_.insert(std::make_pair(id, aux));
}

void AudioSource::ADD_SONG(std::string fileName, std::string id, int loopCount, float volume, float pan)
{
	FMOD::Sound* snd;
	FMOD_CREATESOUNDEXINFO* ErrInf = 0;

	if (loopCount < 0)
		result_ = system_->createSound(fileName.c_str(), FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, ErrInf, &snd);
	else result_ = system_->createSound(fileName.c_str(), FMOD_DEFAULT | FMOD_CREATESTREAM, ErrInf, &snd);

	FMOD_OK_ERROR_CHECK();

	soundValues aux;
	aux.loopCount = loopCount; aux.pan = pan; aux.volume = volume; aux.snd = snd, aux.id_ = id;

	Songs_.insert(std::make_pair(id, aux));
}

void AudioSource::ADD_3D_SOUND(std::string fileName, std::string id, int loopCount, float volume)
{
	FMOD::Sound* snd;
	FMOD_CREATESOUNDEXINFO* ErrInf = 0;

	if (loopCount < 0)
		result_ = system_->createSound(fileName.c_str(), FMOD_3D | FMOD_LOOP_NORMAL, ErrInf, &snd);
	else result_ = system_->createSound(fileName.c_str(), FMOD_3D | FMOD_DEFAULT, ErrInf, &snd);

	FMOD_OK_ERROR_CHECK();

	soundValues3D aux;
	aux.loopCount = loopCount; aux.volume = volume; aux.snd = snd, aux.id_ = id;

	soundList3D_.insert(std::make_pair(id, aux));
}

void AudioSource::PLAY_2D_SOUND(std::string AudioID)
{
	FMOD::Channel* chn;
	auto it = soundList_.find(AudioID);
	if (it != soundList_.end()) {
		result_ = system_->playSound((*it).second.snd, 0, false, &chn);

		chn->setVolume((*it).second.volume);
		chn->setPan((*it).second.pan);
		chn->setLoopCount((*it).second.loopCount);

		FMOD_OK_ERROR_CHECK();
	}
}

void AudioSource::PLAY_3D_SOUND(std::string AudioID, Ogre::Vector3 pos)
{
	FMOD::Channel* chn;
	auto it = soundList3D_.find(AudioID);
	if (it != soundList3D_.end()) {
		result_ = system_->playSound((*it).second.snd, 0, true, &chn);
		(*it).second.emitter.x = &pos.x; (*it).second.emitter.y = &pos.y; (*it).second.emitter.z = &pos.z;
		(*it).second.vel = { 0,0,0 };

		FMOD_VECTOR pos = { pos.x, pos.y, pos.z };

		chn->setVolume((*it).second.volume);
		chn->setLoopCount((*it).second.loopCount);
		chn->set3DAttributes(&pos, &(*it).second.vel);

		FMOD_OK_ERROR_CHECK();
	}
}

void AudioSource::PLAY_SONG(std::string AudioID)
{
	FMOD::Channel* chn;
	auto it = Songs_.find(AudioID);
	if (it != Songs_.end()) {
		result_ = system_->playSound((*it).second.snd, 0, false, &chn);

		chn->setVolume((*it).second.volume);
		chn->setPan((*it).second.pan);
		chn->setLoopCount((*it).second.loopCount);

		FMOD_OK_ERROR_CHECK();
	}
}

void AudioSource::READ_JSON_SOUNDS(std::string file)
{
	json js = GestorRecursos::instance()->getJsonByKey(file);
	for(json d2 : js["2DSounds"])
	ADD_2D_SOUND(d2["rute"], d2["Id"], d2["loopCount"], d2["Volume"], d2["Pan"]);
	for (json d3 : js["3DSounds"])//Sonidos 3D
		ADD_3D_SOUND(d3["rute"], d3["Id"], d3["loopCount"], d3["Volume"]);
	for (json song : js["Songs"])
 		ADD_SONG(song["rute"], song["Id"], song["loopCount"], song["Volume"], song["Pan"]);
}


void AudioSource::set3DFactors(float doppler, float rolloff)
{
	doppler_ = doppler;
	rolloff_ = rolloff;
	system_->set3DSettings(doppler_, 1.0, rolloff_);
}
