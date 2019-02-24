#pragma once
#include <map>
#include <memory>

#include "GameState.h"
#include "MainMenuState.h"
#include "PlayState.h"

enum States { MAIN_MENU, PLAY, OPTIONS, CREDITS };

class SceneManager
{	
private:
	static std::unique_ptr<SceneManager> instance_; // Singleton

	std::map <int , GameState*> states;

	GameState* currentState_;
public:
	SceneManager();
	virtual ~SceneManager();
	static SceneManager* instance();


	GameState* currentState();
	void addState(int stateID, GameState* state);
	void changeState(int stateID);
};