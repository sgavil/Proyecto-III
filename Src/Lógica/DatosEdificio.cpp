#include "DatosEdificio.h"



DatosEdificio::DatosEdificio()
{
}


DatosEdificio::~DatosEdificio()
{
}

void DatosEdificio::load(json file)
{
	json js = ResourceManager::instance()->getJsonByKey("EdificioData.json");

	for (json jsonAux2 : js["Edificios"]) {
		Datos* aux = new Datos();

		json jsonAux = jsonAux2["parameters"];

		if(jsonAux.find("Price") != jsonAux.end())
			addParameter(aux->price_, jsonAux["Price"]);
		if (jsonAux.find("LockedPrice") != jsonAux.end())
			addParameter(aux->LockedPrice_, jsonAux["LockedPrice"]);
		if (jsonAux.find("Locked") != jsonAux.end())
			addParameter(aux->Locked_, jsonAux["Locked"]);

		if (jsonAux.find("PeePee") != jsonAux.end())
			addParameter(aux->PeePeeRestore_, jsonAux["PeePee"]);
		if (jsonAux.find("Hungry") != jsonAux.end())
			addParameter(aux->HungryRestore_, jsonAux["Hungry"]);
		if (jsonAux.find("Fun") != jsonAux.end())
			addParameter(aux->funRestore_, jsonAux["Fun"]);

		if (jsonAux.find("Tam_Cola") != jsonAux.end())
			addParameter(aux->maxCola_, jsonAux["Tam_Cola"]);

		if (jsonAux.find("Tam") != jsonAux.end())
			addParameter(aux->tam.x, jsonAux["Tam"]["x"]);
		if (jsonAux.find("Tam") != jsonAux.end())
			addParameter(aux->tam.y, jsonAux["Tam"]["y"]);

		if (jsonAux.find("Height") != jsonAux.end())
			addParameter(aux->height_, jsonAux["Height"]);

		if (jsonAux.find("Entry") != jsonAux.end())
			addParameter(aux->entry.x, jsonAux["Entry"]["x"]);
		if (jsonAux.find("Entry") != jsonAux.end())
			addParameter(aux->entry.y, jsonAux["Entry"]["y"]);

		if (jsonAux.find("Exit") != jsonAux.end())
			addParameter(aux->exit.x, jsonAux["Exit"]["x"]);
		if (jsonAux.find("Exit") != jsonAux.end())
			addParameter(aux->exit.y, jsonAux["Exit"]["y"]);

		if (jsonAux.find("Duration") != jsonAux.end()) {
			if (addParameter(aux->duration_, jsonAux["Duration"]))
			{
				aux->duration_ *= 1000; //Conversión a milisegundos;
				aux->actDuration_ = aux->duration_;
			}
		}

		if (jsonAux.find("Capacity") != jsonAux.end())
			addParameter(aux->capacity_, jsonAux["Capacity"]);
		if (jsonAux.find("bName") != jsonAux.end())
			addParameter(aux->bName, jsonAux["bName"]);


		datos_.insert(std::make_pair(aux->bName, aux));
	}
}

Datos * DatosEdificio::findData(std::string s)
{
	auto it = datos_.find(s);
	if (it != datos_.end()) {
		return (*it).second;
	}
}

