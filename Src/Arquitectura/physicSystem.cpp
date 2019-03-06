#include "physicSystem.h"

physicSystem* physicSystem::instance_ = nullptr;
btDiscreteDynamicsWorld * physicSystem::dynamicsWorld = nullptr;

std::vector<btCollisionShape*> physicSystem::shapes = std::vector<btCollisionShape*>();


physicSystem::physicSystem()
{
}


physicSystem * physicSystem::instance()
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_ == nullptr)
		instance_ = new physicSystem();
	return instance_;
}

void physicSystem::initPhysics()
{
	// collision configuration contains default setup for memory , collision setup . Advanced users can create their own configuration
	collisionConfiguration = new btDefaultCollisionConfiguration();

	//use the default collision dispatcher . For parallel processing you can use a diffent dispatcher(see Extras / BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	//btDbvtBroadphase is a good general purpose broadphase . You can also try outbtAxis3Sweep .
	overlappingPairCache = new btDbvtBroadphase();

	// the default constraint solver . For parallel processing you can use a different solver (see Extras / BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	//EL MUNDO FÍSICO
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	//Gravedad
	dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void physicSystem::stepSimulation(unsigned int time)
{
	//Actualiza la física
	dynamicsWorld->stepSimulation((float)time / 1000);

	//Información de Debug sobre los Rigidbodys
	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject * obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody * body = btRigidBody::upcast(obj);
		btTransform trans;
		//Está en movimiento
		if (body && body->getMotionState())
			body->getMotionState()->getWorldTransform(trans);
		//Está parado (cogemos la posición inicial)
		else
			trans = obj->getWorldTransform();

		//Informa de la posición
		//printf(" world   pos  object  %d = %f ,%f ,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}
}

void physicSystem::clenaupPhysics()
{
	// remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject * obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody * body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	// delete collision shapes
	for (int j = 0; j< shapes.size(); j++)
	{
		btCollisionShape * shape = shapes[j];
		shapes[j] = 0;
		delete shape;
	}

	// delete dynamics world
	delete dynamicsWorld;

	// delete solver
	delete solver;

	// delete broadphase
	delete overlappingPairCache;

	// delete dispatcher
	delete dispatcher;
}

btRigidBody * physicSystem::createRigidBody( Shape forma, btVector3 position, btScalar dimensions, btScalar mass)
{
	
	btCollisionShape* shape;
	switch (forma)
	{
	case Shape::EmptyShape:
		shape = new btEmptyShape();
		break;
	case Shape::BoxShape:
		shape = new btBoxShape(btVector3(dimensions, dimensions, dimensions));
		break;
	case Shape::SphereShape:
		shape = new btSphereShape(dimensions);
		break;
	case Shape::CapsuleShape:
		shape = new btCapsuleShape(dimensions, dimensions);
		break;
	case Shape::PlaneShape:
		shape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
		break;
	case Shape::CylinderShape:
		shape = new btCylinderShape(btVector3(dimensions, dimensions, dimensions));
		break;
	case Shape::ConeShape:
		shape = new btConeShape(dimensions, dimensions);
		break;
	default:
		break;
	}
	//Añadimos la forma al vector
	shapes.push_back(shape);

	//Posición del rigidbody
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(position);

	//Estado de movimiento empezando en la posición inicial del nodo
	btDefaultMotionState *motionState = new btDefaultMotionState(startTransform);
	//btVector3 localInertia(0, 0, 0);
	
	//Creamos el Rigidbody y lo  añadimos al mundo
	btRigidBody* rigid = new btRigidBody(mass, motionState, shape); //, localInertia)
	rigid->setRestitution(1);
	dynamicsWorld->addRigidBody(rigid);

	//Lo devolvemos
	return rigid;
}




physicSystem::~physicSystem()
{
	
}

