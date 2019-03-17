#pragma once
#include "Components.h"

class BaseCreator
{
public:
	virtual Component* createComponent() const = 0;
	virtual ~BaseCreator() {}
};

class TransformCreator : public BaseCreator
{
public:
	Component* createComponent() const
	{
		Component* e = new Transform();

		return e;
	}
};

class MeshRendererCreator : public BaseCreator
{
public:
	Component* createComponent() const
	{
		Component* e = new MeshRenderer();

		return e;
	}
};

class RigidBodyCreator : public BaseCreator
{
public:
	Component* createComponent() const
	{
		Component* e = new Rigidbody();

		return e;
	}
};

class CameraCreator : public BaseCreator
{
public:
	Component* createComponent() const
	{
		Component* e = new Camera();

		return e;
	}
};

class NPCCreator : public BaseCreator
{
public:
	Component* createComponent() const
	{
		Component* e = new NPC();
		
		return e;
	}
};