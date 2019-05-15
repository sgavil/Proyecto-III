#pragma once

//CEGUI
#include "ResourceManager.h"

#include <memory>
#include <map>

class OgreManager;

//Espacio de nombres de CEGUI (predeclaraciones)
namespace CEGUI
{
	class WindowManager;
	class Window;
	class MouseCursor;
	class PushButton;
	class EventArgs;
	class ProgressBar;
	class PushButton;
}

class HUDManager
{
private:
	static std::unique_ptr<HUDManager> instance_;

	std::map<std::string, CEGUI::Window*> windows;

	CEGUI::WindowManager* windowMgr;
	
	HUDManager();

public:	
	static HUDManager* instance();
	CEGUI::Window* activeWindow;
	void init();

	void addWindow(std::string state);
	void changeWindow(std::string state);

	void setActiveWindow(std::string state);

	//Wrappers
	void showMouseCursor();
	void hideMouseCursor();

	
	CEGUI::Window* createWidget(std::string name, std::string type, float posX, float posY, float offX, float offY, float tamX, float tamY/*, std::string txt, bool(T::* func)(const CEGUI::EventArgs&), T* obj*/);


	//void createText(float posX, float posY, float offsetX, float offsetY, float tamX, float tamY, std::string text);


	~HUDManager();
private:
	friend class OgreManager;

	//Returns mouse cursor
	CEGUI::MouseCursor& getMouseCursor();
};
