#include "SceneManager.h"
#include "ResourceManager.h"
#include "HUDManager.h"

std::unique_ptr<SceneManager> SceneManager::instance_;


void SceneManager::initInstance(bool* ex)
{
	if (instance_.get() == nullptr)
		instance_.reset(new SceneManager(ex));
}

SceneManager* SceneManager::instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}

SceneManager::SceneManager(bool* ex)
{
	exit = ex;
}


void SceneManager::disableOtherStatesNodes()
{
	for (auto s = states.begin(); s != states.end(); s++) {
		(*s).second->getStateNode()->setVisible((*s).second == currentState_);
	}
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
			

GameState* SceneManager::currentState()
{
	return currentState_;
}

GameState* SceneManager::addState(std::string stateID)
{
	GameState* state = new GameState(stateID);
	currentState_ = state;
	state->start();

	states.insert(std::pair<std::string, GameState*>(stateID, state));

	return state;
}

void SceneManager::changeState(std::string stateID)
{
	HUDManager::instance()->changeWindow(stateID);

	auto it = states.find(stateID);

	if (it == states.end())
		currentState_ = addState(stateID);
	else
		currentState_ = it->second;

	disableOtherStatesNodes();
}
