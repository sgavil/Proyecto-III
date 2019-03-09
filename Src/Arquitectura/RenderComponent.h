#pragma once
#include "Component.h""
#include <OgreSceneNode.h>

class RenderComponent : public Component
{
public:

	RenderComponent(Ogre::SceneNode* node);

	~RenderComponent();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(SDL_Event* e, unsigned int time);
	virtual void receive(Message* msg) {};

	virtual Ogre::SceneNode* getNode() { return node_; };

protected:
	Ogre::SceneNode* node_;

};

