#pragma once
#include <iostream>
#include <string>
#include <map>

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <GestorRecursos/gestorDeRecursos.h>
#include <OgreVector3.h>



class AudioSource 
{
	typedef struct {
		float* x;
		float* y;
		float* z;
	} POSITION;

	struct soundValues {
		FMOD::Sound* snd;
		std::string id_;
		float volume;
		float pan;
		int loopCount;
	};

	struct soundValues3D {
		FMOD::Sound* snd;
		std::string id_;
		float volume;
		int loopCount;
		POSITION emitter;
		FMOD_VECTOR vel;
	};

	struct SoundListener {
		POSITION position;
		FMOD_VECTOR vel;
		FMOD_VECTOR up;
		FMOD_VECTOR at;
	};

	std::map<std::string, soundValues> soundList_;
	std::map<std::string, soundValues3D> soundList3D_;
	std::map<std::string, soundValues> Songs_;

public:

	//"Constructora" de la instancia
	static AudioSource* instance(float doppler = 1.0f, float rolloff = 1.0f);

private:
	//Constructora, le llegan los parametros del mundo que afecta a cualquier entidad con sonido 3D
	AudioSource(float doppler = 1.0f, float rolloff = 1.0f);
	

	static std::unique_ptr<AudioSource> instance_;
public:
	~AudioSource();
	
	void ADD_2D_SOUND(std::string fileName, std::string id, int loopCount = 0, float volume = 1, float pan = 0); //Carga de un sonido 2D
	void ADD_SONG(std::string fileName, std::string id, int loopCount = 0, float volume = 1, float pan = 0); //Carga de una canción como stream
	void ADD_3D_SOUND(std::string fileName, std::string id, int loopCount = 0, float volume = 1); //Carga de un sonido 2D
	void PLAY_2D_SOUND(std::string AudioID); //Ejecuci�n de un sonido 2D
	void PLAY_3D_SOUND(std::string AudioID, Ogre::Vector3 pos); //Ejecuci�n de un sonido 3D
	void PLAY_SONG(std::string AudioID); //Ejecuci�n de un sonido 2D

	void READ_JSON_SOUNDS(std::string file);

	//Establece los par�metros del medio
	void set3DFactors(float doppler, float rolloff);



private:
	void FMOD_OK_ERROR_CHECK(); //Comprueba que la variable result es OK lo que significa que todo funciona correctamente
	
	FMOD_RESULT result_; 
	FMOD::System* system_;

	//Variables del medio. Estas variables afectan a todos los sonidos del medio indiferentemente del emisor.
	float doppler_;
	float rolloff_;

};