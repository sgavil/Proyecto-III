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
			

SceneManager* SceneManager::Instance()
{
	if (instance_.get() == nullptr)
		instance_.reset(new SceneManager());

	return instance_.get();
}

GameState* SceneManager::currentState()
{
	return currentState_;
}

GameState* SceneManager::addState(std::string stateID)
{
	GameState* state = new GameState(stateID);

	states.insert(std::pair<std::string, GameState*>(stateID, state));

	return state;
}

void SceneManager::changeState(std::string stateID)
{
	auto it = states.find(stateID);

	if (it == states.end())
		currentState_ = addState(stateID);
	else
		currentState_ = it->second;
}