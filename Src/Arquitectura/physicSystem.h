#pragma once
#include <OgreRoot.h>
#include <memory>
#include <vector>

//Tipo enumerado para los tipos de formas de los RigidBody
enum Shape{ EmptyShape, BoxShape, SphereShape, CapsuleShape, PlaneShape, CylinderShape, ConeShape};
using Vector3 = Ogre::Vector3;
using Quaternion = Ogre::Quaternion;
const Vector3 DEFAULT_GRAVITY = { 0, -10, 0 };

//Forward-declarations
class btRigidBody;
class btCollisionShape;

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

//Clase physXSytem: Singleton para gestionar el sistema de físicas
class PhysicSystem
{
public:

	//Devuelve la instancia
	static PhysicSystem* instance();

	//Inicializa el sistema de físicas
	void initPhysics();

	//Actualiza el sistema
	void stepSimulation(unsigned int time);

	//Limpia la basura
	void clenanupPhysics();

	//Crea un rigidbody con una forma, posición, masa y dimensiones dadas
	static btRigidBody* createRigidBody(Shape forma, Vector3 dimensions, float mass);

	//Aáde una forma al vector 
	void addShape(btCollisionShape* shape);

	//Añade un rigidbody al mundo físico
	void addRigidBody(btRigidBody* rigid);



	//Destructora
	~PhysicSystem();
private:
	//Constructora privada
	PhysicSystem();
	//Instancia
	static std::unique_ptr<PhysicSystem> instance_;

	//Atributos
	//Config. de colisiones
	btDefaultCollisionConfiguration * collisionConfiguration;
	//Dispatcher 
	btCollisionDispatcher * dispatcher;
	//OverlappingPairCache
	btBroadphaseInterface * overlappingPairCache;
	//Solver
	btSequentialImpulseConstraintSolver * solver;
	//Mundo físico
	static btDiscreteDynamicsWorld * dynamicsWorld;

	//Formas
	static std::vector<btCollisionShape*> shapes;
};