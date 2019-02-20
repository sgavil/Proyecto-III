#pragma once
#include <list>
#include <memory>
#include "GameState.h"

class SceneManager
{
private:
	static std::unique_ptr<SceneManager> instance_; // Singleton

	std::list<GameState*> states;
public:
	SceneManager();
	virtual ~SceneManager();
	static SceneManager* instance();


	GameState* currentState();
	void changeState(GameState* state);
};