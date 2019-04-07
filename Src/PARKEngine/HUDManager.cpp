#include "HUDManager.h"

#include "OgreManager.h"
#include "OgreIncludes.h"
#include <functional>



std::unique_ptr<HUDManager> HUDManager::instance_;

HUDManager::HUDManager()
{
}

HUDManager* HUDManager::instance()
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_.get() == nullptr)
		instance_.reset(new HUDManager());

	return instance_.get();
}

void HUDManager::init() 
{
	//Carga de CEGUI y configurado automatico con elementos de OGRE
	CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(OgreManager::instance()->getWindow()));

	//Carga de cosas
	// create (load) the TaharezLook scheme file
	// (this auto-loads the TaharezLook looknfeel and imageset files)
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");

	// create (load) a font.
	// The first font loaded automatically becomes the default font, but note
	// that the scheme might have already loaded a font, so there may already
	// be a default set - if we want the "DejaVuSans-10" font to definitely
	// be the default, we should set the default explicitly afterwards.
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage("TaharezLook/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");

	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);

	///////////////////////////////
	// ARRANCANDO INTERFAZ
	//	- Existen dos formas de hacerlo: Programando la interfaz directamente en c++ o cargandola completa de un archivo xml (layout)
	///////////////////////////////

	//////////////////////////////
	// USANDO C++
	//////////////////////////////

	//Crear ventana Invisible sobre la que construir el interfaz
	windowMgr = CEGUI::WindowManager::getSingletonPtr();		// Obtenemos la ventana de renderizado
	//CEGUI::System::getSingleton().cre
	// myRoot = windowMgr->createWindow("DefaultWindow", "root");		// Creamos una ventana de interfaz con parametros (Tipo ventana definida en Scheme activo, nombre asignado a la ventana)
	//CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot); // Establece que sets de GUI se muestra en el contexto actual, puede cambiarse de uno a otro.

	//Hasta este punto ya se ha creado la ventana invisible sobre la que pondremos los widgets que formaran el menu
	//Vamos a crear elementos sobre esa ventana invisible
	
	//myRoot->addChild(fWnd);
	//fWnd->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber();

	// position a quarter of the way in from the top-left of parent.
	//fWnd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.75f, 0.0f), CEGUI::UDim(0.50f, 0.0f)));
	// set size to be half the size of the parent
	//fWnd->setSize(CEGUI::USize(CEGUI::UDim(0, 50), CEGUI::UDim(0, 50)));
	//fWnd->setMaxSize(CEGUI::USize(CEGUI::UDim(1.0, 0), CEGUI::UDim(1,0)));
	//fWnd->setWidth(CEGUI::UDim(1, 0));
	//fWnd->setHeight(CEGUI::UDim(1, 0));
	//fWnd->setText("LePark!");
	// ¿Este elemento parece que no deja jugar con el tamaño? al menos no se como hacerlo. Los metodos que funcionan en el boton no van aqui.

	//Vamos a meter un boton
	/*CEGUI::PushButton* btn = static_cast<CEGUI::PushButton*>(wmgr.createWindow("TaharezLook/Button", "testButton"));
	myRoot->
	(btn);
	btn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
	btn->setText("BOTONACO");*/

	//fWnd->hide();
	//fWnd->disable();
	//btn->setHeight(CEGUI::UDim(0.1, 0));

	//PARA ACCEDER A WIDGETS SE PUEDE HACER MEDIANTE CEGUI::WINDOW::getChild("ruta en el arbol de widgets omitiendo el root") p.ej: getChild(testWindow)
	// root --|-> testWindow -> myButton			se pueden buscar con getChild(testWindow), getChild(testWindow/myButton), getChild(Button2)
	//		  |-> Button2 


	////////////////////////////////////////////////////////////////////////////////////
	// USANDO ARCHIVOS XML .LAYOUT
	//  - Carga una archivo de REPOSITORIO/Dependencias/cegui-0.8.7/datafiles/layouts/
	//  - Dentro del archivo tiene que estar definidos todos los elementos de la interfaz a mostrar.
	////////////////////////////////////////////////////////////////////////////////////

	/*
	CEGUI::Window* myRoot2 = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("testWindow.layout");	// Cargamos un interfaz de usuario que ya hemos preparado en un archivo XML en los LAYOUTs
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot2);							// Establece que sets de GUI se muestra en el contexto actual, puede cambiarse de uno a otro.
	*/

}



void HUDManager::addWindow(std::string state)
{
	CEGUI::Window* newWindow = windowMgr->createWindow("DefaultWindow", state);
	windows[state] = newWindow;
	// creamos una ventana de interfaz con parametros (tipo ventana definida en scheme activo, nombre asignado a la ventana)
}

void HUDManager::changeWindow(std::string state)
{
	auto it = windows.find(state);

	if (it == windows.end())
		addWindow(state);
		
	setActiveWindow(state);
}

void HUDManager::setActiveWindow(std::string state)
{
	if (activeWindow != nullptr)
	{
		for (size_t i = 0; i < activeWindow->getChildCount(); i++)
		{
			activeWindow->getChildAtIdx(i)->disable();
			activeWindow->getChildAtIdx(i)->hide();
		}
	}

	activeWindow = windows[state];

	for (size_t i = 0; i < activeWindow->getChildCount(); i++)
	{
		activeWindow->getChildAtIdx(i)->enable();
		activeWindow->getChildAtIdx(i)->show();
	}

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(activeWindow); // establece que sets de gui se muestra en el contexto actual, puede cambiarse de uno a otro.
}


HUDManager::~HUDManager()
{
}
