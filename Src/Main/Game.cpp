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
#include <Arquitectura/Camera.h>
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
		
		// I capture the keyboard settings.
	// Then I update the scene according to these informations.
		OIS::Keyboard* lKeyboard = OgreSystem::instance()->getKeyboard();
		OIS::Mouse* lMouse = OgreSystem::instance()->getMouse();

		

		// The current time is used in the calculation : this is 'real time'. 
		// The camera move with the same speed on any computer.
		// I put a coefficient 200.0 because the scene is big.
		// I test the keys TGFH for moving.
		lKeyboard->capture();
		{
			float lCoeff = 200.0f * actualTime;
			Ogre::Vector3 lTranslation(Ogre::Vector3::ZERO);
			if (lKeyboard->isKeyDown(OIS::KC_W))
			{
				ScnMng_->currentState()->getEntity("Camera")->getComponent<Camera>()->getCameraNode()->translate({0, 0, -10}, Ogre::Node::TS_LOCAL);
			}
			if (lKeyboard->isKeyDown(OIS::KC_S))
			{
				ScnMng_->currentState()->getEntity("Camera")->getComponent<Camera>()->getCameraNode()->translate({ 0, 0, 10 }, Ogre::Node::TS_LOCAL);
			}
			if (lKeyboard->isKeyDown(OIS::KC_A))
			{
				ScnMng_->currentState()->getEntity("Camera")->getComponent<Camera>()->getCameraNode()->translate({ -10, 0, 0 }, Ogre::Node::TS_LOCAL);
			}
			if (lKeyboard->isKeyDown(OIS::KC_D))
			{
				ScnMng_->currentState()->getEntity("Camera")->getComponent<Camera>()->getCameraNode()->translate({ 10, 0, 0 }, Ogre::Node::TS_LOCAL);
			}
			if (lTranslation != Ogre::Vector3::ZERO)
			{
				ScnMng_->currentState()->getEntity("Camera")->getComponent<Camera>()->getCameraNode()->translate(lTranslation, Ogre::Node::TS_LOCAL);
			}
		}

		// same for the mouse.
		lMouse->capture();
		{
			const OIS::MouseState& lMouseState = lMouse->getMouseState();
			if (lMouseState.buttonDown(OIS::MB_Left))
			{
				// I change the colour of the background...
				float red = Ogre::Math::RangeRandom(0.1f, 0.9f);
				float green = Ogre::Math::RangeRandom(0.1f, 0.9f);
				float blue = Ogre::Math::RangeRandom(0.1f, 0.9f);
				ScnMng_->currentState()->getEntity("Camera")->getComponent<Camera>()->getViewport()->setBackgroundColour(Ogre::ColourValue(red, green, blue));
			}
			float lMouseX = float(lMouseState.X.rel) / float(OgreSystem::instance()->getWindow()->getWidth());
			float lMouseY = float(lMouseState.Y.rel) / float(OgreSystem::instance()->getWindow()->getHeight());
			float lRotCoeff = -5.0f;
			Ogre::Radian lAngleX(lMouseX * lRotCoeff);
			Ogre::Radian lAngleY(lMouseY * lRotCoeff);

			// If the 'player' don't make loopings, 'yaw in world' + 'pitch in local' is often enough for a camera controler.
			ScnMng_->currentState()->getEntity("Camera")->getComponent<Camera>()->getCameraNode()->yaw(lAngleX, Ogre::Node::TS_WORLD);
			ScnMng_->currentState()->getEntity("Camera")->getComponent<Camera>()->getCameraNode()->pitch(lAngleY, Ogre::Node::TS_LOCAL);
		}

	}
}