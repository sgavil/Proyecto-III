#pragma once
#include "Component.h"

#include <OgreAnimationState.h>

class Animation : public Component
{
public:
	Animation();
	~Animation();

	virtual void update(unsigned int time);

	virtual void load(json file);

	virtual void save(json file) {};

	void changeAnimation(std::string anim);

	void disableAnimation();
	void enableAnimation();

private:
	Ogre::AnimationState* currentAnim;
	bool loop;

	bool enabledInStart;

	std::string initAnim;
};

REGISTER_TYPE(Animation);

