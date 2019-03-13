#include "EntityFactory.h"

std::unique_ptr<EntityFactory> EntityFactory::instance_;

EntityFactory::EntityFactory()
{
	BaseCreator* bs;
	bs = new CameraComponentCreator();
	registerType("CameraComponent", bs);

    bs = new NPCComponentCreator();
	registerType("NPCComponent", bs);
}





EntityFactory::~EntityFactory()
{
	for (auto&& m : creators_)
		delete m.second;

	creators_.clear();
}

EntityFactory* EntityFactory::Instance()
{
	if (instance_.get() == nullptr)
		instance_.reset(new EntityFactory());
	return instance_.get();
}


bool EntityFactory::registerType(std::string typeID, BaseCreator * pCreator)
{
	std::map<std::string, BaseCreator*>::iterator it = creators_.find(typeID);

	if (it != creators_.end())
	{
		delete pCreator;
		return false;
	}

	creators_[typeID] = pCreator;
	return true;
}

Entity * EntityFactory::createEntity(json file)
{
	Entity* entity = new Entity();
	entity->setName(file["name"]);

	for (json comp : file["Components"])
	{
		Component* c = createComponent(comp["name"]);
		entity->addComponent(c);
		c->load(comp);
	}

	return entity;
}

Component * EntityFactory::createComponent(std::string name)
{
	auto it = creators_.find(name);

	BaseCreator* compCreator = it->second;

	return compCreator->createComponent();
}