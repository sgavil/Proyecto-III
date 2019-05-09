#pragma once
#include "TextBox.h"
#include "HUDManager.h"
#include <Lógica/BureaucracyManager.h>

class DatosEdificio;
class Datos;
class PriceTextBox : public TextBox
{

public:
	PriceTextBox();
	~PriceTextBox();

	void load(json file);

	virtual void update(unsigned int time);
	virtual void receive(Message* msg) {};

	virtual void save(json& file) {};

	void changeTextPrice();

private:
	std::string buildName_;
	DatosEdificio* datosEdificio_;
	Datos* datos_;
	BureauCrazyManager* bureauCrazyManager_;

};

REGISTER_TYPE(PriceTextBox)