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
	void createButton(float posX, float posY, float offsetX, float offsetY, float tamX, float tamY, std::string text, bool(T::* function)(const CEGUI::EventArgs&), T* obj)
	{
		CEGUI::Window* button = windowMgr->createWindow("AlfiskoSkin/Button", text + "Button");

		button->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, offsetX), CEGUI::UDim(posY, offsetY)));
		button->setSize(CEGUI::USize(CEGUI::UDim(0, tamX), CEGUI::UDim(0, tamY)));
		button->setText(text);

		button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(function, obj));

		activeWindow->addChild(button);
	}
	void createText(float posX, float posY, float offsetX, float offsetY, float tamX, float tamY, std::string text);

	~HUDManager();
};
