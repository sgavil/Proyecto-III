#include "SceneManager.h"


PlayState::PlayState(Ogre::SceneManager* scnMgn, Ogre::RenderWindow* wind) : GameState(), scnMgn_(scnMgn), wind_(wind)
{
	start();
}

PlayState::~PlayState()
{
}


void PlayState::start()
{
	// Inicializar componentes de la propia escena, así como crear las escenas accesibles desde la misma (comprobar antes si está ya creada)
	camera = new Entity();
	camComp = new CameraComponent(scnMgn_, wind_);
	scene.push_back(camComp);
	camera->addComponent(camComp);
}


void PlayState::update(unsigned int time)
{
	GameState::update(time);
}

void PlayState::render(unsigned int time)
{
	GameState::render(time);
}

void PlayState::handleInput()
{
	GameState::handleInput();
}