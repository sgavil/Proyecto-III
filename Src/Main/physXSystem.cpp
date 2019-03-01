#include "physXSystem.h"
#include "RenderUtils.hpp"

physXSystem* physXSystem::instance_ = nullptr;

//Recursos de PhysX
PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = nullptr;
PxPhysics*				gPhysics = nullptr;


PxMaterial*				gMaterial = nullptr;

PxPvd*                  gPvd = nullptr;

PxDefaultCpuDispatcher*	gDispatcher = nullptr;
PxScene*				gScene = nullptr;
ContactReportCallback gContactReportCallback;

//Gravedad de la escena
const Vector3 GRAVITY = { 0,-10,0 };

physXSystem::physXSystem()
{
	initPhysics(false);
}


physXSystem * physXSystem::instance()
{
	if (instance_ == nullptr)
		instance_ = new physXSystem();
	return instance_;
}

//interactive: true if the game is rendering, false if it offline
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = GRAVITY;
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
}

// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
}


void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// ---------------------------s--------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

	//TODO
	//...
}

void onCollision(PxActor* actor1, PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	//TODO
	//...
}

void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{

	case 'B':
		break;
	default:
		break;
	}
}


physXSystem::~physXSystem()
{
}



//En el main:
//Para la detección de basura
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#ifndef OFFLINE_EXECUTION 
//extern void renderLoop();
//renderLoop();
//#else
//static const PxU32 frameCount = 100;
//initPhysics(false);
//for (PxU32 i = 0; i<frameCount; i++)
//	stepPhysics(false);
//cleanupPhysics(false);
//#endif
