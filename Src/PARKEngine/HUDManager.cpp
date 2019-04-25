#include "HUDManager.h"
#include "SceneManager.h"
#include "OgreManager.h"
#include "OgreIncludes.h"


using namespace std::placeholders;

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

	windowMgr = CEGUI::WindowManager::getSingletonPtr();		// Obtenemos la ventana de renderizado
}


CEGUI::MouseCursor& HUDManager::getMouseCursor()
{
	return CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor();
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
		activeWindow->hide();

	activeWindow = windows[state];

	activeWindow->show();


	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(activeWindow); // establece que sets de gui se muestra en el contexto actual, puede cambiarse de uno a otro.
}



void HUDManager::createText(float posX, float posY, float offsetX, float offsetY, float tamX, float tamY, std::string text)
{
	CEGUI::Window* text_window = windowMgr->createWindow("TaharezLook/StaticText", "Textonuevo");
	CEGUI::DefaultWindow* textWindow = static_cast<CEGUI::DefaultWindow*>(text_window);

	/*Colocacion*/
	textWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, offsetX), CEGUI::UDim(posY, offsetY)));
	textWindow->setSize(CEGUI::USize(CEGUI::UDim(0, tamX), CEGUI::UDim(0, tamY)));

	/*Especifico del editbox*/
	textWindow->setText(text);
	
	activeWindow->addChild(textWindow);

}

HUDManager::~HUDManager()
{
}
