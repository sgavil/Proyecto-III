#include "EntityFactory.h"

std::unique_ptr<EntityFactory> EntityFactory::instance_;

EntityFactory::EntityFactory()
{
	blueprints = GestorRecursos::instance()->getJsonByKey("Entities.json");
	BaseCreator* bs;

	// En los archivos Json, al añadir un componente hay que usar el nombre que aquí se utilice
	bs = new TransformCreator();
	registerType("Transform", bs);

	bs = new MeshRendererCreator();
	registerType("MeshRenderer", bs);

	bs = new RigidBodyCreator();
	registerType("Rigidbody", bs);

	bs = new CameraCreator();
	registerType("Camera", bs);

    bs = new NPCCreator();
	registerType("NPC", bs);

	bs = new ButtonCreator();
	registerType("Button", bs);
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

Entity* EntityFactory::createEntity(json file)
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

Entity* EntityFactory::createEntityFromBlueprint(std::string name)
{
	Entity* entity = new Entity();
	entity->setName(name);

	for (std::string comp : blueprints[name])
	{
		Component* c = createComponent(comp);
		entity->addComponent(c);
	}

	return entity;
}

Component* EntityFactory::createComponent(std::string name)
{
	auto it = creators_.find(name);

	BaseCreator* compCreator = it->second;

	return compCreator->createComponent();
}