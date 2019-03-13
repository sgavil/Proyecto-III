#include "NPCComponent.h"
#include <iostream>
NPCComponent::NPCComponent()
{
}

NPCComponent::~NPCComponent()
{
}

void NPCComponent::load(json file)
{
	hunger = file["hunger"];
	thirst = file["thirst"];
}