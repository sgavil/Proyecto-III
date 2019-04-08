#include "Edificio.h"
#include <PARKEngine/PARKFoundation.h>
#include "NPC.h"
#include "Matrix/Node.h"



Edificio::Edificio()
{
}


Edificio::~Edificio()
{
}

void Edificio::update(unsigned int time)
{
	actDuration_ -= time;

	if (actDuration_ <= 0) {
		sacar();
		montar();
		actDuration_ = duration_;
	}
}

void Edificio::encolar(Entity * e)
{
	if (cola.size() < maxCola_)
		cola.push(e);
}

void Edificio::montar()
{
	for (int i = 0; i < capacity_; i++) {
		if (!cola.empty()) {
			rideing.push_back(cola.front());
			cola.pop();
		}
	}
}

void Edificio::sacar()
{
	for (int i = 0; i < rideing.size(); i++) {
		if (!rideing.empty()) {
			Entity* e = rideing.front();
			rideing.pop_front();
			e->setActive(true);
			//e->getComponent<NPC>()->setNode(ExitNode->getComponent<Node>());
		}
	}
}



void Edificio::load(json file)
{
	PeePeeRestore_ = file["PeePee"];
	HungryRestore_ = file["Hungry"];
	funRestore_ = file["Fun"];
	maxCola_ = file["Tam_Cola"];

	tam.x = file["Tam"]["x"];
	tam.y = file["Tam"]["y"];

	height_ = file["Height"];

	entry.x = file["Entry"]["x"];
	entry.y = file["Entry"]["y"];

	exit.x = file["Exit"]["x"];
	exit.y = file["Exit"]["y"];

	duration_ = file["Duration"] * 1000; //Conversión a milisegundos;
	actDuration_ = duration_;
	capacity_ = file["Capacity"];
	setName(file["bName"]);
}
