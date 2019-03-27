#pragma once

#include <GestorRecursos/gestorDeRecursos.h>

class Ogre::RenderWindow;
class Ogre::Root;
class Ogre::Light;
class Ogre::Plane;
class Ogre::RenderWindow;

class OgreSystem
{
public:
	//"Constructora" de la instancia
	static OgreSystem* instance(std::string initFileJson);

	//Devuelve la instancia
	static OgreSystem* instance();

	~OgreSystem();

	//Renderiza la escena (deltaTime debe estar en segundos)
	void render(unsigned int deltaTime);

	

	//Metodos getter
	Ogre::SceneManager * getSM();
	Ogre::RenderWindow* getWindow() { return window_; };
	Ogre::Light* getLight() { return light_; };
	unsigned long gethWnd() { return hWnd; }

private:

	//Constructora privada
	OgreSystem(std::string initFileJson);
	//Instancia
	static std::unique_ptr<OgreSystem> instance_;
	

	Ogre::Root *root_;
	Ogre::RenderWindow *window_;
	Ogre::SceneManager *sceneMgr_;

	Ogre::Light* light_;

	Ogre::Plane plane_;

	json initFile;
	//void ceguiInit();
	/*Utiliza el root para crear una ventana de nombre APP_NAME , tamaño WINDOW_HEIGHT/WIDHT ademas de crear
	una camara y asociarle un viewport a esta*/

	unsigned long hWnd; //Variable que toma la ventana de Ogre para aplicarla a la de SDL

	void initWindow();
};
