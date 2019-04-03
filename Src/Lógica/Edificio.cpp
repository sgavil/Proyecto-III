#include "Edificio.h"



Edificio::Edificio()
{
}


Edificio::~Edificio()
{
}

void Edificio::load(json file)
{
	PeePeeRestore_ = file["PeePee"];
	HungryRestore_ = file["Hungry"];
	funRestore_ = file["Fun"];
	maxCola_ = file["Tam_Cola"];
	type_ = file["Type"];

	tam.x = file["Tam"]["x"];
	tam.y = file["Tam"]["y"];

	entry.x = file["Entry"]["x"];
	entry.y = file["Entry"]["y"];

	exit.x = file["Exit"]["x"];
	exit.y = file["Exit"]["y"];
}
