#pragma once
#include "PARKEngine/Component.h"

class Edificio;
class TextBox;
class FrameWindowBox;
class NPC;

class BureauCrazyManager : public Component
{
	//Tipos de impuestos
	enum TaxType
	{
		ELECTRIC_TAX,MAINTENANCE_TAX,
	};

	struct TaxBill	//Recibos de los impuestos ( Cantidad + tipo )
	{
		TaxType taxType_;
		//Cantidad de dinero que resta este impuesto
		float amount_;
	};

public:
	BureauCrazyManager();
	~BureauCrazyManager();

	//Comprueba si esta en bancarrota
	bool bankruptcy(); 
	
	//Resetea el tiempo
	void resetTimer();

	virtual void load(json file);

	virtual void update(unsigned int time);

	void addUnlockedBuilding(const Edificio& building);

	virtual void receive(Message* msg);


	bool isBuildingUnlocked(const Edificio& building);
	
	void addMoney(float f);
	float getActualMoney() { return actualMoney_; };

	// Metodo para mostrar las necesidades del NPC
	void showNPCInfoBars(NPC* npc);

	void setSelectedNPC(NPC* npc);

	virtual std::string getInfo() { return "BureaucracyManager"; };

private:
	//Panel donde se muestran las necesidades del NPC
	FrameWindowBox* infoNPC_;

	void updateMoneyText();

	//A partir de un valor definido de dinero actual comienza a tener en cuenta el proceso de bancarrota
	void checkBankRuptcy(); 

	//Resta la cantidad que haya definida actualmente de un impuesto
	void taxCollect(TaxType taxType);

	////Resta las cantidades definidas de todos los impuestos declarados
	void taxCollectALL();

	void addAmountToTax(TaxType type, float amount);
	void changeTaxAmount(TaxType type, float amount);

	float actualMoney_;
	int visitors_;
	int totalVisitors_;
	std::vector<TaxBill> bills_;

	//Tiempo maximo que puede estar un jugador en negativo antes que se declare la bancarrota
	float ruptcyMaxTime_;

	//Tiempo en el que se empieza a contar para la bancarrota
	float ruptcyStartTime_;

	//Dinero a partir del cual se empieza a cronometrar la bancarrota del jugador
	float floorRuptcyMoney_;

	//Tiempo restante para cobrar los siguientes impuestos
	float Time2Tax_;

	//Informa si se ha empezado o no a contar para la bancarrota
	bool startedToCount_;

	bool bankruptcy_;
	bool electric = false;
	bool maintenance = false;//Para controlar las output de los impuestos

	//Lista de atracciones desbloqueadas
	std::list<Edificio> unlockedBuildings_;

	TextBox* textDinero_;
	TextBox* infoDinero_;
	TextBox* infoImpuestos_;
	TextBox* nextTax_;

	TextBox* infoNumPersonas_;

	TextBox* infoNumPersonasTotales_;

	//NPC seleccionado
	NPC* selectedNPC_;

	double ingTime_;

	std::clock_t start;

	void timer();

	int electricidadCobrado = -1;
	int mantenimientoCobrado = -1;

	int seconds, hours, minutes;

	void cobradorImpuestos();
};
REGISTER_TYPE(BureauCrazyManager);