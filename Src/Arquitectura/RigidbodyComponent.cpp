#include "RigidbodyComponent.h"



RigidbodyComponent::RigidbodyComponent()
{
	//TODO: Método createRigidBody
	//CAJA
	btBoxShape* boxShape = new btBoxShape(btVector3(10, 10, 10));
	physicSystem::instance()->addShape(boxShape);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(0, 30, 0));


	btRigidBody* box = new btRigidBody(1, 0, boxShape, btVector3(0, 0, 0));
	box->setWorldTransform(startTransform);
	physicSystem::instance()->addRigidBody(box);
}


RigidbodyComponent::~RigidbodyComponent()
{
}

void RigidbodyComponent::update(unsigned int time)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			//EXIT = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				std::cout << "Hola! Soy Rigidbody" << std::endl;
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{

			}
		}
	}
}
