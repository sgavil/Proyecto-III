#include "NPC.h"
#include <iostream>
#include  <PARKEngine/Entity.h>
#include <PARKEngine/PARKComponents.h>
#include <PARKEngine/OgreIncludes.h>

NPC::NPC()
{
}

NPC::~NPC()
{
}
void NPC::start()
{
	
}

void NPC::update(unsigned int time)
{
	entity_->getComponent<Transform>()->rotate(Vector3::UNIT_Y, 2);
	entity_->getComponent<Transform>()->translate(Vector3(1, 0, 0));
	//entity_->getComponent<Transform>()->rotate(Vector3::UNIT_Y, 1.0);
	//std::cout << "Hola, soy " << entity_->getName() << " y tengo \n Hambre: " << hunger_ << "\n Pipí: " << peepee_ << "\n Diversión: " << fun_ << std::endl;
}

void NPC::load(json file)
{
	hunger_ = file["hunger"];
	peepee_ = file["peepee"];
	fun_ = file["fun"];
}