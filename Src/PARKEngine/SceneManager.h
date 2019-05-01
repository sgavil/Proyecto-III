#pragma once
#include <map>
#include <memory>
#include "GameState.h"

class SceneManager
{
private:
	static std::unique_ptr<SceneManager> instance_; // Singleton

	std::map <std::string, GameState*> states; // Estados del juego

	GameState* currentState_; // Estado activo

	bool* exit;

	void disableOtherStatesNodes();

public:
	SceneManager();
	virtual ~SceneManager();

	// ·> Devuelve un puntero al SceneManager, o lo crea si no lo estaba ya
	static SceneManager* instance();

	void setExit(bool* ex) {
		exit = ex; 
	}

	void exitGame() {
		*exit = true; 
	}


	// ·> Devuelve el estado activo actualmente
	GameState* currentState();

	// ·> Crea y añade un nuevo estado al SceneManager
	GameState* addState(std::string stateID);

	// ·> Cambia de estado por el indicado por parámetro. En caso de no existir, lo crea
	void changeState(std::string stateID);
};