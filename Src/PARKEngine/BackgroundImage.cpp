#include "BackgroundImage.h"

BackgroundImage::BackgroundImage()
{
}

BackgroundImage::~BackgroundImage()
{
}

void BackgroundImage::load(json file)
{
	std::string nombre;

	nombre = file["ImageName"].get<std::string>();

	HUDManager::instance()->createBackground(nombre);
}
