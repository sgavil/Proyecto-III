#pragma once

//CEGUI
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include <memory>
#include <map>

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

	//Returns mouse cursor
	CEGUI::MouseCursor& getMouseCursor();

	void addWindow(std::string state);
	void changeWindow(std::string state);

	void setActiveWindow(std::string state);

	template<typename T>
	void createButton(std::string name, float posX, float posY, float offX, float offY, float tamX, float tamY, std::string txt, bool(T::* func)(const CEGUI::EventArgs&), T* obj)
	{
		CEGUI::Window* button = windowMgr->createWindow("AlfiskoSkin/Button", name);

		button->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, offX), CEGUI::UDim(posY, offY)));
		button->setSize(CEGUI::USize(CEGUI::UDim(0, tamX), CEGUI::UDim(0, tamY)));
		button->setText(txt);

		button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(func, obj));

		activeWindow->addChild(button);
	}
	void createText(float posX, float posY, float offsetX, float offsetY, float tamX, float tamY, std::string text);

	~HUDManager();
};
