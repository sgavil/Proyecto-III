#include "NPC.h"
#include <iostream>
#include  <PARKEngine/Entity.h>
#include <PARKEngine/PARKComponents.h>
#include <PARKEngine/OgreIncludes.h>
#include <PARKEngine/ResouRceManager.h>

NPC::NPC()
{
}

NPC::~NPC()
{
}
void NPC::start()
{
	//entity_->getComponent<Rigidbody>()->setPosition(entity_->getComponent<Rigidbody>()->getPosition() + Vector3(-500, 0, 0));
	//entity_->getComponent<MeshRenderer>()->setMaterial("Ogre.material");
	
}

void NPC::update(unsigned int time)
{
	//std::cout << entity_->getComponent<MeshRenderer>()->getMaterial() << std::endl;
	//entity_->getComponent<Transform>()->rotate(Vector3::UNIT_Y, 2);
	//entity_->getComponent<Transform>()->translate(Vector3(1, 0, 0));
	//entity_->getComponent<Rigidbody>()->setPosition(entity_->getComponent<Rigidbody>()->getPosition() + Vector3(-500, 0, 0));
	//std::cout << entity_->getComponent<Rigidbody>()->getInfo();
	//entity_->getComponent<Transform>()->scale(Vector3(0.9, 0.9, 0.9));
	//std::cout << "Hola, soy " << entity_->getName() << " y tengo \n Hambre: " << hunger_ << "\n Pipí: " << peepee_ << "\n Diversión: " << fun_ << std::endl;
}

void NPC::load(json file)
{
	hunger_ = file["hunger"];
	peepee_ = file["peepee"];
	fun_ = file["fun"];
}