#pragma once
//#include "callbacks.hpp"
#include "RenderUtils.hpp"

using namespace physx;


//Inicializa el sistema de físicas
void initPhysics(bool interactive);
//Actualiza el sistema
void stepPhysics(bool interactive, double t);
//Gestión del input
void keyPress(unsigned char key, const PxTransform& camera);
//Control de colisiones
void onCollision(PxActor* actor1, PxActor* actor2);
//Libera los recursos
void cleanupPhysics(bool interactive);


//Clase physXSytem: Singleton para gestionar el sistema de físicas
class physXSystem
{
public:
	//Devuelve la instancia
	static physXSystem* instance();

	//Destructora
	~physXSystem();
private:	
	//Constructora privada
	physXSystem();
	//Instancia
	static physXSystem* instance_;

};
