#pragma once
#include <map>
#include <memory>
#include "GameState.h"

class SceneManager
{	
private:
	static std::unique_ptr<SceneManager> instance_; // Singleton

	std::map <std::string, GameState*> states;

	GameState* currentState_;
public:
	SceneManager();
	virtual ~SceneManager();
	static SceneManager* instance();


	GameState* currentState();
	void addState(std::string stateID);
	void changeState(std::string stateID);
};