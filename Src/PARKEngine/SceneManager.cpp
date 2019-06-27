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
	GameState* state = nullptr;

	//Solo lo añadimos si no está ya
	auto it = states.find(stateID);
	if(it == states.end())
	{
		//Primero añadimos una ventana y creamos el estado
		HUDManager::instance()->addWindow(stateID);
		HUDManager::instance()->changeWindow(stateID);
		state = new GameState(stateID);

		//Añadimos el estado
		states.insert(std::pair<std::string, GameState*>(stateID, state));

		//Volvemos a la ventana en la que estábamos
		if(currentState_ != nullptr)
			HUDManager::instance()->changeWindow(currentState_->getID());
	}
	return state;
}

void SceneManager::changeState(std::string stateID)
{
	HUDManager::instance()->changeWindow(stateID);

	auto it = states.find(stateID);
	assert(it != states.end());
	currentState_ = it->second;
	currentState_->start();

	disableOtherStatesNodes();
}

bool SceneManager::removeState(std::string stateID) {
	//Generamos un iterador para que busque el estado deseado
	auto it = states.find(stateID);

	//Si no lo ha encontrado (Posición final)
	if (it == states.end())
		return false;
	else {
		delete it->second;
		states.erase(it);
		return true;
	}

}
