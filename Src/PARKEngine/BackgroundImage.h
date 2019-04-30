#pragma once
#include "Component.h"
#include "HUDManager.h"

class BackgroundImage : public Component
{

public:
	BackgroundImage();
	~BackgroundImage();

	virtual void save(json& file) {};

	void load(json file);

};

REGISTER_TYPE(BackgroundImage)