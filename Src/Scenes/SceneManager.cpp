#include "SceneManager.h"

std::unique_ptr<SceneManager> SceneManager::instance_;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	auto it = states.begin();
	while (it != states.end()) it = states.erase(it);

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

void SceneManager::addState(int stateID, GameState* state)
{
	states.insert(std::pair<int, GameState*>(stateID, state));
}

void SceneManager::changeState(int stateID)
{
	currentState_ = states.find(stateID)->second;
}