#pragma once

#include <map>
#include <vector>
#include <memory>

class Entity;
class Component;

class BaseCreator
{
public:
	virtual Component* createComponent() const = 0;
};


class EntityFactory
{
private:
	EntityFactory();

	static std::unique_ptr<EntityFactory> instance_;

	//static std::map<std::string, BaseCreator*> creators_;

	Component* createComponent(std::string name);
	static std::map<std::string, BaseCreator*>& creators();

public:
	static EntityFactory* Instance();
	~EntityFactory();

	static void registerType(std::string typeID, BaseCreator* pCreator);
	std::vector<Entity*> createEntities(std::string stateID);
	//Entity* createEntity(json file);
	Entity* createEntityFromBlueprint(std::string name);
};