#pragma once
#include <memory>
#include <map>

//CEGUI
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>


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
	void setActiveWindow(CEGUI::Window* window);

	template<typename T>
	void createButton(float posX, float posY, float offsetX, float offsetY, float tamX, float tamY, std::string text, bool(T::*function)(const CEGUI::EventArgs&), T* obj);

	~HUDManager();
};

template<typename T>
inline void HUDManager::createButton(float posX, float posY, float offsetX, float offsetY, float tamX, float tamY, std::string text, bool(T::* function)(const CEGUI::EventArgs &), T * obj)
{
	CEGUI::Window* wnd = windowMgr->createWindow("TaharezLook/Button", text + "Button");

	wnd->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, offsetX), CEGUI::UDim(posY, offsetY)));
	wnd->setSize(CEGUI::USize(CEGUI::UDim(0, tamX), CEGUI::UDim(0, tamY)));
	//CEGUI::PushButton* button = static_cast<CEGUI::PushButton*>(wnd);
	wnd->setText(text);

	wnd->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(function, obj));

	activeWindow->addChild(wnd);
}
