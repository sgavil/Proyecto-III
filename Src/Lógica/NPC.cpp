#include "NPC.h"
#include <iostream>
#include  <PARKEngine/Entity.h>
#include <PARKEngine/PARKComponents.h>
#include <PARKEngine/OgreIncludes.h>
#include <PARKEngine/ResouRceManager.h>
#include <PARKEngine/SceneManager.h>

NPC::NPC()
{
}

NPC::~NPC()
{
}
void NPC::start()
{
	std::vector<Entity*> entities = SceneManager::instance()->currentState()->getEntitiesWithComponent<Transform>();
	for (Entity* e : entities)
		std::cout << "ENTITY: " << e->getName() <<  std::endl;
	//entity_->getComponent<Rigidbody>()->setPosition(entity_->getComponent<Rigidbody>()->getPosition() + Vector3(-500, 0, 0));
	//entity_->getComponent<MeshRenderer>()->setMaterial("Ogre.material");
	
}

void NPC::update(unsigned int time)
{
	//std::cout << entity_->getComponent<MeshRenderer>()->getMaterial() << std::endl;
	//entity_->getComponent<Transform>()->rotate(Vector3::UNIT_Y, 2);
	//entity_->getComponent<Transform>()->translate(Vector3(1, 0, 0));
	//entity_->getComponent<Rigidbody>()->setPosition(entity_->getComponent<Rigidbody>()->getPosition() + Vector3(-500, 0, 0));
	//std::cout << entity_->getComponent<Rigidbody>()->getInfo();
	//entity_->getComponent<Transform>()->scale(Vector3(0.9, 0.9, 0.9));
	//std::cout << "Hola, soy " << entity_->getName() << " y tengo \n Hambre: " << hunger_ << "\n Pipí: " << peepee_ << "\n Diversión: " << fun_ << std::endl;
}

void NPC::load(json file)
{
	hunger_ = file["hunger"];
	peepee_ = file["peepee"];
	fun_ = file["fun"];
}

//void relax(const AristaDirigida<int>& e)
//	{
//		int v = e.from(), w = e.to();
//		if (timeTo[w] > timeTo[v] + e.valor())
//		{
//			//Añadimos el tiempo de espera de la página en si
//			timeTo[w] = timeTo[v] + e.valor();
//			//En la función update se contempla que la clave no estuviera ya
//			pq.update(w, timeTo[w]);
//		}
//	}

//Inicializamos las distancias a infinito
//		for (int v = 0; v < N_; v++)
//			timeTo[v] = numeric_limits<int>::max();
//
//		//Metemos el 0 con distancia 0
//		timeTo[0] = 0;
//		pq.push(0, 0);
//
//		//Vamos metiendo y sacando elementos de la cola de prioridades variables
//		while (!pq.empty())
//		{
//			IndexPQ<int>::Par v = pq.top();
//			pq.pop();
//			//timeTo[v.elem] += tCarga[v.elem];
//			for (AristaDirigida<int> e : g.ady(v.elem))
//				relax(e);
//		}