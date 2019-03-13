#pragma once
#include "Component.h"

/*
Clase Entidad:
-> Es un simple contenedor de omponentes, los cuales definen su comportamiento.
-> Hereda de Listener (para recibir mensajes) y de Emitter (para enviarlos).
-> Tiene una referencia a su RigidBody (de physx) para el motor físico
*/
class Entity 
{
public:
	//Constructora por defecto
	Entity();
	//Constructora con los componentes ya dados en un vector
	Entity(std::vector<Component*> comps, std::string name = "undefined"); 

	 //Añade un componente a la entidad
	void addComponent(Component* comp);
	//Elimina un componente de la entidad. Devuelve "true" si la entidad tenía ese componente, "false" e.o.c
	bool delComponent(Component* comp);
	
	//Devueve la lista de componentes de la Entidad
	std::vector<Component*> getComponents() { return components_; }

	//Devuelve un componente con un nombre específico
	Component * getComponent(Name name);

	//Devuelve el nombre de la propia entidad
	std::string getName() { return name_; };

	//Otorga un nombre a la entidad
	void setName(std::string name) { name_ = name; };
	
	//Destructora
	virtual ~Entity();
private:
	//Vector de componentes genérico (no se diferencian por el tipo de componente)
	std::vector<Component*> components_;
	std::string name_;
};
