#include "Game.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "BureaucracyManager.h"
//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/Renderer.h>

// INCLUDES TEMPORALES PARA LAS ENTIDADES
#include <Arquitectura/Transform.h>
#include <Arquitectura/Rigidbody.h>
#include <Arquitectura/MeshRenderer.h>
#include <Arquitectura/Terrain.h>
//#include <Arquitectura/Camera.h>

Game::Game(std::string basicConfig):exit(false)
{
	ogreSyst_ = OgreSystem::instance(basicConfig);
	GestorRecursos::instance()->ceguiInit();
	audioSrc_ = AudioSource::instance();
	ScnMng_ = SceneManager::instance();
	physSyst_ = physicSystem::instance();
}

Game::~Game()
{
	if (physSyst_ != nullptr)
		delete physSyst_;
	if (audioSrc_ != nullptr)
		delete audioSrc_;
	if (ScnMng_ != nullptr)
		delete ScnMng_;
	if (ogreSyst_ != nullptr)
		delete ogreSyst_;
	//CEGUI::System::destroy();
	//CEGUI::OgreRenderer::destroy(static_cast<CEGUI::OgreRenderer&>()//*d_renderer));
}

void Game::start()
{
	ScnMng_->addState("StateTest");
	ScnMng_->changeState("StateTest");

	//--------------------------TEST DE REPRODUCCION DE SONIDO--------------------------//

	AudioSource::instance()->READ_JSON_SOUNDS("AudioSource.json");
	AudioSource::instance()->PLAY_2D_SOUND("cochecitos");

	//Start
	ScnMng_->currentState()->start();
}

void Game::run()
{
	//Tiempo entre frames y tiempo total transcurrido
	unsigned int deltaTime, actualTime;
	actualTime = deltaTime = SDL_GetTicks();
	//Bucle principal
	while (!exit)
	{
		//Llama al update, handleInput y render de la escena activa
		ScnMng_->currentState()->update(deltaTime);
		exit = ScnMng_->currentState()->handleInput(deltaTime);
		ogreSyst_->render(deltaTime);

		//Actualiza el deltaTime
		deltaTime = SDL_GetTicks() - actualTime;
		actualTime = SDL_GetTicks();
	}
}