#include "SceneManager.h"
#include <GestorRecursos/gestorDeRecursos.h>

std::unique_ptr<SceneManager> SceneManager::instance_;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	auto it = states.begin();
	while (it != states.end())
	{
		delete (*it).second;
		(*it).second = nullptr;
		++it;
	}
	
	//it = states.erase(it);
		
	states.clear();
	instance_.release();
}
			

SceneManager* SceneManager::instance()
{
	if (instance_.get() == nullptr)
		instance_.reset(new SceneManager());

	return instance_.get();
}

GameState* SceneManager::currentState()
{
	return currentState_;
}

void SceneManager::addState(std::string stateID)
{
	json file = GestorRecursos::instance()->getJsonByKey(stateID + ".json");

	GameState* state = new GameState(file);

	states.insert(std::pair<std::string, GameState*>(stateID, state));

}

void SceneManager::changeState(std::string stateID)
{
	currentState_ = states.find(stateID)->second;
}