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
	std::pair<int, int> tam; //este tamaño hace referncia al numero de nodos que ocupa en la matriz logica
	std::pair<int, int> entry; //Coordenada de entrada con respecto al (0, 0) de la atracción 
	std::pair<int, int> exit; //Coordenada de salida con respecto al (0, 0) de la atracción 

public:
	Edificio();
	~Edificio();

	//Actualización del componente
	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};

	void load(json file) {};

	//GETTERS
	int getPeePeeValue() { return PeePeeRestore_; };
	int getHungryValue() { return HungryRestore_; };
	int getFunValue() { return funRestore_; };

	int getTamX() { return tam.first; };
	int getTamY() { return tam.second; };

	int getEntryX() { return entry.first; };
	int getEntryY() { return entry.second; };

	int getExitX() { return exit.first; };
	int getExitY() { return exit.second; }

	std::pair<int, int> getTamAsPair() { return tam; };
	std::pair<int, int> getEntryAsPair() { return entry; };
	std::pair<int, int> getExitAsPair() { return exit; };

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
