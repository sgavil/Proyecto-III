#pragma once
#include <PARKEngine/Component.h>
#include <queue>
#include <string>
#include <PARKEngine/ResourceManager.h>


class Edificio : public Component
{
public:
	bool Edificio::operator ==(const Edificio& a) {
		return bName == a.bName;
	}
	//El tipo ornament no tiene ni entrada ni salida, su cola es de 0 y no cambia valores de necesidades
	enum type { Amusement, Shop, Toilet, Ornament };
private:
	//Estos son los valores que un edificio modifica de un NPC
	//si estos son negativos disminuiran la necesidad del NPC
	//en caso de ser nulos no afectan y positivo la aumenta
	int PeePeeRestore_;
	int HungryRestore_;
	int funRestore_;

	std::string bName; //Nombre de la atracción
	int maxCola_; //Tamaño máximo de la cola, si esta está llena no se podrá acceder a ella
	int duration_; //En milisegundos, La de Ornament debe ser 0
	int actDuration_;
	int capacity_; //La de ornament debe ser 0

	type type_; //El tipo d ela atracción

	std::queue<Entity*> cola;
	std::list<Entity*> rideing;
	Ogre::Vector2 tam;
	int height_;
	Ogre::Vector2 entry;
	Ogre::Vector2 exit;

	Entity* EntryNode;
	Entity* ExitNode;

public:
	Edificio();
	~Edificio();

	//Actualización del componente
	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};

	void encolar(Entity* e);
	void montar();
	void sacar();

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
	int getExitY() { return exit.y; };
	//
	Ogre::Vector2 getTam() { return tam; };
	Ogre::Vector2 getEntry() { return entry; };
	Ogre::Vector2 getExit() { return exit; };

	int getHeight() { return height_; };

	//Devuelve la duración de la atracción en milisegundos
	int getDuration() { return duration_; };

	std::string getBuildingName() { return bName; };

	//SETTERS
	void getPeePeeValue(int P) { PeePeeRestore_ = P; };
	void setHungryValue(int H) { HungryRestore_ = H; };
	void setFunValue(int F) { funRestore_ = F; };
	//El parametro d es en segundos y automaticamente lo pasa a milisegundos que es como trabaja internamente
	void setDuration(int D) { duration_ = D * 1000; };

	void setEntryNode(Entity* e) { EntryNode = e; };
	void setExitNode(Entity* e) { ExitNode = e; };
private:
	//Es privado porque solo se debe establecer al Establecer de json la atracción y no en ejecución
	void setType(type t) { type_ = t; };
	//Es mejor que en el Json al ser solo 4 tipos de valores lea un int para no tener que ir interpretando el string constantemente
	void setTypeByInt(int t) { if (t < sizeof(type)) type_ = type(t); };
	//establece el nombre del edificio
	void setName(std::string s) { bName = s; };
};

REGISTER_TYPE(Edificio);
