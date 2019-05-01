#pragma once
#include <vector>
#include <list>
#include <OgreSceneNode.h>

class Component;
class Entity;

class GameState
{
private:
	Ogre::SceneNode* stateNode;

protected:
	std::list<Component*> scene; // Componentes de la escena

public:
	GameState(std::string stateID);
	virtual ~GameState();

	virtual void start();

	virtual void update(unsigned int time);
	virtual void render(unsigned int time);
	virtual bool handleInput(unsigned int time);

	// �> A�ade una entidad a la escena
	void addEntity(Entity* e);

	// �> A�ade un grupo de entidades a la escena 
	void addEntities(std::vector<Entity*> ent);

	// �> Elimina una entidad de la escena. Devuelve 'true' si estaba en la escena, 'false' e.o.c
	bool removeEntity(std::string name);

	// �> Devuelve una entidad de la escena
	Entity* getEntity(std::string name);

	//Devuelve una lista de entidades que tengan el componente especificado
	template<typename T>
	std::vector<Entity*> getEntitiesWithComponent()
	{
		std::vector<Entity*> v;
		//Busca el componente
		for (Component* c : scene) {
			T* component = dynamic_cast<T*>(c);
			if (component != nullptr)
				v.push_back(component->getEntity());
		}
		return v;
	};

	// �> Devuelve la escena
	std::list<Component*> getScene();

	Ogre::SceneNode* getStateNode();
};