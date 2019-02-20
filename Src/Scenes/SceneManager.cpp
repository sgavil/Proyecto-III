#include "SceneManager.h"

std::unique_ptr<SceneManager> SceneManager::instance_;

SceneManager::~SceneManager()
{
	for (GameState* s : states) delete s;
}

SceneManager::SceneManager()
{
}

SceneManager* SceneManager::instance()
{
	if (instance_.get() == nullptr)
		instance_.reset(new SceneManager());

	return instance_.get();
}

GameState* SceneManager::currentState()
{
	return nullptr;
}

void SceneManager::changeState(GameState* state)
{
}