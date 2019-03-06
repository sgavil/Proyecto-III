#pragma once
#include <list>
#include <Arquitectura/Component.h>
#include <Arquitectura/physicSystem.h>


class GameState
{
protected:
	std::vector<Component*> scene; // Componentes en la escena

	virtual void start() = 0;
public:
	GameState();
	virtual ~GameState();

	virtual void update(unsigned int time);
	virtual void render(unsigned int time);
	virtual void handleInput(unsigned int time);

	void addComponent(Component* c) { scene.push_back(c); }
	std::vector<Component*> getScene() { return scene; };
};