#include "Edificio.h"
#include <PARKEngine/Entity.h>
#include "NPC.h"
#include "Edificio.h"
#include <PARKEngine/Entity.h>
#include "NPC.h"
#include "Matrix/Node.h"
#include "PARKEngine/PARKComponents.h"



Edificio::Edificio()
{
}


Edificio::~Edificio()
{
}

void Edificio::update(unsigned int time)
{
	//Tiene cola, aforo, etc. (no es un camino)

	if (type_ != BuildingType::Ornament)
	{
		actDuration_ -= time;

		if (actDuration_ <= 0) {
			sacar();
			montar();
			actDuration_ = duration_;
		}
	}
}

bool Edificio::encolar(Entity * e)
{
	if (cola.size() < maxCola_)
		cola.push(e);
	else
		return false;
	return true;
}

void Edificio::montar()
{
	for (int i = 0; i < capacity_; i++) {
		if (!cola.empty()) {
			Entity* e = cola.front();
			e->getComponent<MeshRenderer>()->setVisible(false);
			e->getComponent<NPC>()->enterAttraction();
			rideing.push_back(cola.front());
			cola.pop();
		}
	}
}

void Edificio::sacar()
{
	while (!rideing.empty()) {
		Entity* e = rideing.front();
		rideing.pop_front();
		e->getComponent<MeshRenderer>()->setVisible(true);
		e->getComponent<NPC>()->getOutofAttraction();
	}
}



void Edificio::load(json file)
{
	addParameter(price_, file["Price"]);
	setTypeByInt(file["Type"]);

	addParameter(PeePeeRestore_, file["PeePee"]);
	addParameter(HungryRestore_, file["Hungry"]);
	addParameter(funRestore_, file["Fun"]);

	addParameter(maxCola_, file["Tam_Cola"]);

	addParameter(tam.x, file["Tam"]["x"]);
	addParameter(tam.y, file["Tam"]["y"]);

	addParameter(height_, file["Height"]);

	addParameter(entry.x, file["Entry"]["x"]);
	addParameter(entry.y, file["Entry"]["y"]);

	addParameter(exit.x, file["Exit"]["x"]);
	addParameter(exit.y, file["Exit"]["y"]);

	if (addParameter(duration_, file["Duration"]))
	{
		duration_ *= 1000; //Conversión a milisegundos;
		actDuration_ = duration_;
	}

	addParameter(capacity_, file["Capacity"]);
	addParameter(bName, file["bName"]);
}
