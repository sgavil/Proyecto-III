#include "WindowBox.h"
#include "SceneManager.h"
#include "Button.h"
#include "TextBox.h"
#include "ProgressBar.h"
#include "ImageBox.h"
#include "CallbackManager.h"

WindowBox::WindowBox()
{
	type = "TaharezLook/StaticText";
}

WindowBox::~WindowBox()
{
}

void WindowBox::load(json file)
{
	Widget::load(file);

	//Mover el panel
	window->setProperty("DragMovingEnabled", "False");
	window->setProperty("AutoRenderingSurface", "False");

	//Para las propiedades del boton de cerrar
	string closeEnabled = file["closeEnabled"];
	window->setProperty("CloseButtonEnabled", closeEnabled);
	if (closeEnabled == "True") {
		addParameter(closeCallback, file["callback"]);
		addParameter(closeCallbackBackParam, file["parameter"]);
		window->getChildElement("__auto_closebutton__")->subscribeEvent(CEGUI::PushButton::EventClicked, &WindowBox::onClick, this);
	}

	//Opciones para el titulo
	string titleEnabled = file["titleEnabled"];
	window->setProperty("FrameEnabled", titleEnabled);
	if (titleEnabled == "True") {
		string title = file["title"];
		window->setProperty("Text", title);
		string titleFont = file["font"];
		window->setProperty("TitlebarFont", titleFont);
	}

	//Para los hijos del panel
	for (json h : file["Hijos"]) {
		hijos.push_back(h["name"]);
	}

	
	if (file["active"] == "False")
		window->hide();
	else 
		window->show();
}

void WindowBox::start()
{
	for (string s : hijos) {
		Entity* e = SceneManager::instance()->currentState()->getEntity(s);
		if (e->getComponent<Button>() != nullptr)
			window->addChild(SceneManager::instance()->currentState()->getEntity(s)->getComponent<Button>()->getPushButton());
		else if (e->getComponent<TextBox>() != nullptr)
			window->addChild(SceneManager::instance()->currentState()->getEntity(s)->getComponent<TextBox>()->getStaticText());
		else if (e->getComponent<ProgressBar>() != nullptr)
			window->addChild(SceneManager::instance()->currentState()->getEntity(s)->getComponent<ProgressBar>()->getProgressBar());
		else if (e->getComponent<ImageBox>() != nullptr)
			window->addChild(SceneManager::instance()->currentState()->getEntity(s)->getComponent<ImageBox>()->getStaticImage());
	}
}

bool WindowBox::closeWindow(const CEGUI::EventArgs & e)
{
	window->hide();
	return true;
}

bool WindowBox::onClick(const CEGUI::EventArgs& e)
{
	CallbackManager::instance()->getCallback(closeCallback)(closeCallbackBackParam);
	return true;
}
