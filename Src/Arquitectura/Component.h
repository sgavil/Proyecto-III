#pragma once

//No hacer #include "Entity.h" para evitar inclusión circular
class Entity;

/*
Clase Componente:
-> Define un comportamiento específico.
-> Contiene métodos para pintarse, gestionar eventos y actualizar lógica.
-> Tiene un flag de actividad y un puntero a la entidad a la que está asociado.
* Esta clase padre es abstracta, ya que no define ningún comportamiento.
*/
class Component
{
public:
	//Constructora por defecto
	Component();

	//Métodos principales (renderizado, lógica y eventos)
	virtual void render(unsigned int time) = 0;
	virtual void update(unsigned int time) = 0;
	virtual void handleEvent() = 0;

	//Getters y setters del flag de actividad
	bool isActive() { return active_; };
	void setActive(bool b) { active_ = b; };

	//Getters y setters de la entidad
	void setEntity(Entity* ent) { entity_ = ent; };

	//Destructora
	virtual ~Component();
private:
	//Flag de actividad
	bool active_;
	//Puntero a la entidad
	Entity* entity_;
};


