#include "Component.h"
#include "Messages.h"

using namespace Architecture;
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
	//Constructora con los componentes ya dados y el RigidBody
	Entity(std::vector<Component*> comps); //, RigidBody* r = nullptr);

	 //Añade un componente a la entidad
	void addComponent(Component* comp);
	//Elimina un componente de la entidad. Devuelve "true" si la entidad tenía ese componente, "false" e.o.c
	bool delComponent(Component* comp);

	//Métodos de Listener y Emitter
	
	//Devuelve el Rigidbody de la entidad
	//RigidBody* getRigid(){return rigid_;};
	//Establece el RigidBody de la entidad (si tenía ya uno, lo borra)
	//void setRigid(RigidBody* r){if(rigid_ != nullptr) delete rigid_; rigid_ = r;}

	//Destructora
	virtual ~Entity();
private:
	//Vector de componentes genérico (no se diferencian por el tipo de componente)
	std::vector<Component*> components_;
};
