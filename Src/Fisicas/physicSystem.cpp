#include "physicSystem.h"

physicSystem* physicSystem::instance_ = nullptr;


physicSystem::physicSystem()
{
}


physicSystem * physicSystem::instance()
{
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



	//EJEMPLO: TENEMOS UN PLANO RECTANGULAR Y UN CUBO QUE CAERÁ SOBRE ÉL. EL PLANO ES ESTÁTICO(masa = 0)
	//SUELO
	//Creamos una forma y la añadimos al vector
	btBoxShape* groundShape = new btBoxShape(btVector3(50, 1, 50));
	shapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, 0, 0));

	//Creamos el rigidbody a partir de la forma y lo añadimos al mundo en la posición (0,0,0)
	//masa, 
	btRigidBody* ground = new btRigidBody(0,0, groundShape, btVector3(0,0,0));
	//body->setWorldTransform(groundTransform);
	dynamicsWorld->addRigidBody(ground);


	//CAJA
	btBoxShape* boxShape = new btBoxShape(btVector3(10, 10, 10));
	shapes.push_back(boxShape);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(0, 30, 0));


	btRigidBody* box = new btRigidBody(1, 0, boxShape, btVector3(0, 0, 0));
	box->setWorldTransform(startTransform);
	dynamicsWorld->addRigidBody(box);
}

void physicSystem::stepSimulation()
{
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

	// print positions of all objects
	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject * obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody * body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);

		}
		else
		{
			trans = obj->getWorldTransform();
		}
		printf(" world   pos  object  %d = %f ,%f ,%f\n", j, float(trans.getOrigin().getX()), float(
			trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
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




physicSystem::~physicSystem()
{
	
}

