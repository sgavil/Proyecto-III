#include "NPC.h"
#include <iostream>
#include  <PARKEngine/Entity.h>
#include <PARKEngine/PARKComponents.h>

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
	//std::cout << "Hola, soy " << entity_->getName() << " y tengo \n Hambre: " << hunger_ << "\n Pipí: " << peepee_ << "\n Diversión: " << fun_ << std::endl;
}

void NPC::load(json file)
{
	hunger_ = file["hunger"];
	peepee_ = file["peepee"];
	fun_ = file["fun"];
}