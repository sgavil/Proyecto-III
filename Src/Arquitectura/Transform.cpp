#include "Transform.h"


Transform::Transform():position_(Ogre::Vector3(0,0,0)), orientation_(Ogre::Quaternion::IDENTITY), scale_(Ogre::Vector3(1,1,1))
{
}

Transform::Transform(Ogre::Vector3 position, Ogre::Quaternion orientation, Ogre::Vector3 scale)
	:position_(position), orientation_(orientation), scale_(scale)
{
}

void Transform::load(json file)
{
	json pos = file["position"];
	position_.x = pos["x"];
	position_.y = pos["y"];
	position_.z = pos["z"];

	//json scale = file["scale"];
	//scale_.x = scale["x"];
	//scale_.y = scale["y"];
	//scale_.z = scale["z"];
}

Transform::~Transform()
{
}

void Transform::update(unsigned int time)
{

}

bool Transform::handleEvent(SDL_Event* e, unsigned int time)
{
	if (e->type == SDL_KEYDOWN)
	{
		//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
		if (e->key.keysym.sym == SDLK_SPACE)
		{
			//foo
		}
	}
	return false;
}
