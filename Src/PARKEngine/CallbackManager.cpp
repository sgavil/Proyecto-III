#include "CallbackManager.h"

#include "SceneManager.h"

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
