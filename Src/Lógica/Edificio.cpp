#include "Edificio.h"
#include <PARKEngine/Entity.h>
#include "NPC.h"
#include "Edificio.h"
#include <PARKEngine/Entity.h>
#include "NPC.h"
#include "Matrix/Node.h"
#include "PARKEngine/PARKComponents.h"
#include <PARKEngine/SceneManager.h>



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
		datos->actDuration_ -= time;

		if (datos->actDuration_ <= 0) {
			sacar();
			montar();
			datos->actDuration_ = datos->duration_;
		}
	}
}

bool Edificio::encolar(Entity * e)
{
	if (cola.size() < datos->maxCola_)
		cola.push(e);
	else
		return false;
	return true;
}

void Edificio::montar()
{
	for (int i = 0; i < datos->capacity_; i++) {
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

	setTypeByInt(file["Type"]);


	datos = SceneManager::instance()->currentState()->getEntity("DatosEdificios")->getComponent<DatosEdificio>()->findData(file["bName"]);
}
