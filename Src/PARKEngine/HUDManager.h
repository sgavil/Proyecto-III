#pragma once
#include "Utils.h"

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

	CEGUI::Window* activeWindow;
	
	HUDManager();

public:	
	static HUDManager* instance();

	void init();

	void addWindow(std::string state);
	void changeWindow(std::string state);

	CEGUI::Window* getActiveWindow();
	void setActiveWindow(std::string state);

	// Wrappers
	void showMouseCursor();
	void hideMouseCursor();

	
	CEGUI::Window* createWidget(std::string name, std::string type, float posX, float posY, float offX, float offY, float tamX, float tamY);


	~HUDManager();
private:
	friend class OgreManager;

	//Returns mouse cursor
	CEGUI::MouseCursor& getMouseCursor();
};
