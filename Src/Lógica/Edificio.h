#pragma once
#include <PARKEngine/Component.h>
#include <queue>
#include <string>
#include <PARKEngine/ResourceManager.h>

class Edificio : public Component
{
public:
	//El tipo ornament no tiene ni entrada ni salida, su cola es de 0 y no cambia valores de necesidades
	enum type { Amusement, Shop, Toilet, Ornament }; 
private:
	//Estos son los valores que un edificio modifica de un NPC
	//si estos son negativos disminuiran la necesidad del NPC
	//en caso de ser nulos no afectan y positivo la aumenta
	int PeePeeRestore_;
	int HungryRestore_;
	int funRestore_;

	int maxCola_; //Tamaño máximo de la cola, si esta está llena no se podrá acceder a ella
	
	type type_;
	
	std::queue<Entity*> cola;
	Ogre::Vector2 tam;
	Ogre::Vector2 entry;
	Ogre::Vector2 exit;

public:
	Edificio();
	~Edificio();

	//Actualización del componente
	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};

	void load(json file);

	//GETTERS
	int getPeePeeValue() { return PeePeeRestore_; };
	int getHungryValue() { return HungryRestore_; };
	int getFunValue() { return funRestore_; };
	//Para obtener las coordenadas de forma individual
	int getTamX() { return tam.x; };
	int getTamY() { return tam.y; };

	int getEntryX() { return entry.x; };
	int getEntryY() { return entry.y; };

	int getExitX() { return exit.x; };
	int getExitY() { return exit.y; }
	//
	Ogre::Vector2 getTam() { return tam; };
	Ogre::Vector2 getEntry() { return entry; };
	Ogre::Vector2 getExit() { return exit; };

	//SETTERS
	void getPeePeeValue(int P) { PeePeeRestore_ = P; };
	void setHungryValue(int H) { HungryRestore_ = H; };
	void setFunValue(int F) { funRestore_ = F; };
private:
	//Es privado porque solo se debe establecer al Establecer de json la atracción y no en ejecución
	void setType(type t) { type_ = t; };
	//Es mejor que en el Json al ser solo 4 tipos de valores lea un int para no tener que ir interpretando el string constantemente
	void setTypeByInt(int t) { if(t < sizeof(type)) type_ = type(t); }; 
};

REGISTER_TYPE(Edificio);
