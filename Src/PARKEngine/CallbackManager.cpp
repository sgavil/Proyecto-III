#include "CallbackManager.h"
#include "Lógica/ConstructionMode.h"
#include "Entity.h"

#include "SceneManager.h"
#include "AudioManager.h"

using namespace std::placeholders;

std::unique_ptr<CallbackManager> CallbackManager::instance_;


CallbackManager::CallbackManager()
{
	initCallbacks();
}
CallbackManager::~CallbackManager()
{
}

CallbackManager* CallbackManager::instance()
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_.get() == nullptr)
		instance_.reset(new CallbackManager());

	return instance_.get();
}


std::function<void(std::string)> CallbackManager::getCallback(std::string name)
{
	return callbacks[name];
}

template <typename T>
void CallbackManager::addCallback(std::string keyName, bool(T::*cb)(std::string), T* obj)
{
	callbacks[keyName] = std::bind(cb, obj, _1);
}


void CallbackManager::initCallbacks()
{
	addCallback("onChangeState", &CallbackManager::onChangeState, this);
	addCallback("onExit", &CallbackManager::onExit, this);
	addCallback("construct", &CallbackManager::construct, this);
}



// -------------- CALLBACKS -------------- //


bool CallbackManager::onExit(std::string null)
{
	SceneManager::instance()->exitGame();
	return true;
}

bool CallbackManager::onChangeState(std::string state)
{
	SceneManager::instance()->changeState(state);
	return true;
}

bool CallbackManager::EffectVolumeChange(std::string vol)
{
	if (vol == "+") AudioManager::instance()->UP_EFFECTS_VOLUME();
	else if (vol == "-") AudioManager::instance()->DOWN_EFFECTS_VOLUME();
	return true;
}

bool CallbackManager::MusicVolumeChange(std::string vol)
{
	if (vol == "+") AudioManager::instance()->UP_MUSIC_VOLUME();
	else if (vol == "-") AudioManager::instance()->DOWN_MUSIC_VOLUME();
	return true;
}

bool CallbackManager::construct(std::string buildName)
{
	Entity* e = SceneManager::instance()->currentState()->getEntity("ConstructionMode");
	e->getComponent<ConstructionMode>()->construct(buildName);
	return true;
}
