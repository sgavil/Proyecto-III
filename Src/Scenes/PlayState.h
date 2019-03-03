#pragma once
#include <Main/CameraComponent.h>

class  PlayState : public GameState
{
protected:

	virtual void start();
public:
	PlayState(Ogre::SceneManager* scnMgn, Ogre::RenderWindow* wind);
	virtual ~PlayState();

	void update(unsigned int time);
	void render(unsigned int time);
	void handleInput();

	Entity* camera;
	CameraComponent* camComp;

	Ogre::SceneManager* scnMgn_;
	Ogre::RenderWindow* wind_;
};