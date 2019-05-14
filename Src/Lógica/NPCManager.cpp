#include "NPCManager.h"
#include <PARKEngine/PARKEngine.h>
#include "NPC.h"

NPCManager::NPCManager(): actualTime_(0)
{

}

NPCManager::~NPCManager()
{

}

void NPCManager::load(json file)
{
	addParameter(enterTime_, file["enterTime"]); 
	enterTime_ *= 1000; //ms
}


void NPCManager::update(unsigned int time)
{
	actualTime_ += time;
	if(actualTime_>=enterTime_)
	{
		//Spams NPC
		Entity* npc = EntityFactory::Instance()->createEntityFromBlueprint("NPC");
		SceneManager::instance()->currentState()->addEntity(npc);
		npc->start();

		actualTime_ = 0;
	}
}

bool NPCManager::handleEvent(unsigned int time)
{
	
	return false;
}


void NPCManager::receive(Message * msg)
{

}



