#include "EntityFactory.h"
#include "Entity.h"
std::unique_ptr<EntityFactory> EntityFactory::instance_;

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}



EntityFactory* EntityFactory::Instance()
{
	if (instance_.get() == nullptr)
		instance_.reset(new EntityFactory());
	return instance_.get();
}


void EntityFactory::registerType(std::string creatorName, BaseCreator* pCreator)
{
	creators()[creatorName] = pCreator;
}


std::vector<Entity*> EntityFactory::createEntities(std::string stateID)
{
	json file = GestorRecursos::instance()->getJsonByKey(stateID + ".json");

	std::vector<Entity*> entities;
	std::map<std::string, Component*> dic;
	for (json ent : file["Entities"])
	{
		Entity* entity = new Entity();
		entity->setName(ent["name"]);

		for (json comp : ent["Components"])
		{
			Component* c = createComponent(comp["name"]);
			entity->addComponent(c);
			c->load(comp);
			dic[comp["name"]] = c;
			for (json j : comp["Listeners"])
			{
				c->registerListener(dic[j["name"]]);
			}
		}

		entities.push_back(entity);
	}

	return entities;
}


Entity* EntityFactory::createEntityFromBlueprint(std::string name)
{
	Entity* entity = new Entity();
	entity->setName(name);

	json blueprints = GestorRecursos::instance()->getJsonByKey("Entities.json");

	for (json comp : blueprints[name])
	{
		Component* c = createComponent(comp["name"]);
		entity->addComponent(c);

		if (comp.find("parameters") != comp.end())
			c->load(comp["parameters"]);
	}
	
	return entity;
}


Component* EntityFactory::createComponent(std::string name)
{
	auto it = creators().find(name);

	BaseCreator* compCreator = it->second;

	return compCreator->createComponent();
}

std::map<std::string, BaseCreator*>& EntityFactory::creators()
{
	static std::map<std::string, BaseCreator*>* map = new std::map<std::string, BaseCreator*>();
		   
	return *map;
}