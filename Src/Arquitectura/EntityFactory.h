#pragma once
#include "Entity.h"
#include "ComponentCreator.h"
#include <map>
#include <memory>



class EntityFactory
{

private:
	EntityFactory();

	static std::unique_ptr<EntityFactory> instance_;

	std::map<std::string, BaseCreator*> creators_;

	json blueprints;

	Component* createComponent(std::string name);
public:
	static EntityFactory* Instance();
	~EntityFactory();

	bool registerType(std::string typeID, BaseCreator* pCreator);
	Entity* createEntity(json file);
	Entity* createEntityFromBlueprint(std::string name);
};