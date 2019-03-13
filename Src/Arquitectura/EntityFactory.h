#pragma once
#include "Entity.h"
#include "ComponentCreator.h"
#include <map>
#include <memory>



class EntityFactory
{

private:
	EntityFactory()
	{
		BaseCreator* bs = new NPCComponentCreator();
		registerType("NPCComponent", bs);
	}

	static std::unique_ptr<EntityFactory> instance_;

	std::map<std::string, BaseCreator*> m_creators;

public:
	static EntityFactory* Instance()
	{
		if (instance_.get() == nullptr)
			instance_.reset(new EntityFactory());
		return instance_.get();
	}

	~EntityFactory() {
		for (auto&& m : m_creators) {
			delete m.second;
		}
		m_creators.clear();
	};

	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if (it != m_creators.end())
		{
			delete pCreator;
			return false;
		}

		m_creators[typeID] = pCreator;
		return true;
	}

	Entity* createEntity(json file)
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

	Component* createComponent(std::string name)
	{
		auto it = m_creators.find(name);

		BaseCreator* compCreator = it->second;

		return compCreator->createComponent();
	}
};

/*
{
	"NPC":
	[
		{
			"componet": "hambreComponent",
			"hambre": 10,
			"sed": "mucha",
			"dinero": 5.60,
		}
	]
}

{
	"NPC":
	[
		{
			"hambreComponent":
			{
				"hambre": 10,
				"sed": "mucha",
				"dinero": 5.60,
			}
		}

		{
			"mearComponent":
			{
				"hambre": 10,
				"sed": "mucha",
				"dinero": 5.60,
			}
		}
	]
}



vector<Component> v;
for(int i = 0; i < tamDic; i++){
	Componente comp = new ComponenteFactory::createComponent(dic[i]);
	v.push_back(comp);
}

Entity* entity = new Entity(v, nombre);


//Factoria Componente
map.insert("hambreComponent", new HambreComponent());

Component* createComponent(diccionario){
	Component c = map[diccionario];
	c->load(diccionario);
}
*/