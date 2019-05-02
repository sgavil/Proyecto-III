#include "BureaucracyManager.h"
#include "Edificio.h"
#include <PARKEngine/PARKEngine.h>
#include <PARKEngine/TextBox.h>
#include "NPC.h"
#include <ctime>
#include <cmath>

BureauCrazyManager::BureauCrazyManager() : startedToCount_(false), bankruptcy_(false)
, ruptcyStartTime_(0), textDinero_(nullptr)
{

}

BureauCrazyManager::~BureauCrazyManager()
{

}

void BureauCrazyManager::checkBankRuptcy()
{
	
	if (!startedToCount_ && actualMoney_ < floorRuptcyMoney_) {
		ruptcyStartTime_ = clock(); //Empieza a contar
		startedToCount_ = true;
	}
	
	if (startedToCount_ && (((clock() - ruptcyStartTime_) / CLOCKS_PER_SEC ) >= ruptcyMaxTime_)) //Ha superado el tiempo maximo que se puede estar en negativo
	{
		bankruptcy_ = true;

	}
	if (actualMoney_ > floorRuptcyMoney_) { //Si vuelvo a estar en positivo dejo de contar
		startedToCount_ = false;
	}
}

void BureauCrazyManager::taxCollect(TaxType taxType)
{
	actualMoney_ -= bills_[taxType].amount_;
}

void BureauCrazyManager::taxCollectALL()
{
	for (TaxBill t : bills_) {
		actualMoney_ -= t.amount_;
	}
}

void BureauCrazyManager::addAmountToTax(TaxType type, float amount)
{
	bills_[type].amount_ += amount;
}

void BureauCrazyManager::changeTaxAmount(TaxType type, float amount)
{
	bills_[type].amount_ = amount;
}



bool BureauCrazyManager::bankruptcy()
{
	return bankruptcy_;
}

void BureauCrazyManager::load(json file)
{
	for (json taxes : file["Taxes"])
	{
		TaxBill bill = { TaxType(taxes["Id"]), taxes["Amount"] };
		bills_.push_back(bill);
	}

	ruptcyMaxTime_ = file["BankRuptcy"]["ruptcyMaxTime"] ;
	floorRuptcyMoney_ = file["BankRuptcy"]["floorRuptcyMoney"];
	Time2Tax_ = file["BankRuptcy"]["InitialTime2Tax"];
	actualMoney_ = file["BankRuptcy"]["ActualMoney"];
	visitors_ = file["BankRuptcy"]["InitVisitors"];
}


void BureauCrazyManager::update(unsigned int time)
{

	checkBankRuptcy();

	if (bankruptcy())
	{
		send(&Message(BANKRUPTCY));
		
	}

	if (textDinero_ == nullptr) {
		textDinero_ = SceneManager::instance()->currentState()->getEntity("TextDinero")->getComponent<TextBox>();
		textDinero_->setText(std::to_string((int)actualMoney_) + " $");
	}
	if (infoDinero_ == nullptr) {
		infoDinero_ = SceneManager::instance()->currentState()->getEntity("InfoDinero")->getComponent<TextBox>();
		infoDinero_->setText("Dinero actual: " + std::to_string((int)actualMoney_) + " $");
	}
}

bool BureauCrazyManager::handleEvent(unsigned int time)
{
	//Spawnea un NPC en la entrada del parque
	if (InputManager::getSingletonPtr()->isKeyDown("SpamNPC"))
	{
		Entity* npc = EntityFactory::Instance()->createEntityFromBlueprint("NPC");
		SceneManager::instance()->currentState()->addEntity(npc);
		npc->start();
	}
	else if (InputManager::getSingletonPtr()->isKeyDown("SelectNPC"))
	{
		pair<Entity*, Ogre::Vector3> nodeAndPos = OgreManager::instance()->raycastToMouse();
		Entity* selected = nodeAndPos.first;
		if(selected != nullptr && selected->getComponent<NPC>() != nullptr)
			std::cout << selected->getComponent<NPC>()->getInfo();

	}
	return false;
}



void BureauCrazyManager::addUnlockedBuilding(const Edificio & building)
{
	unlockedBuildings_.push_back(building);
}

void BureauCrazyManager::receive(Message * msg)
{
	switch (msg->mType_)
	{
	case COLLECT_ALL_TAXES:
		taxCollectALL();
		break;
	case NEW_UNLOCKED_BUILDING:
		break;
	case IS_BUILDING_UNLOCKED:
	{
		IsBuildingUnlocked* unlMsg = static_cast<IsBuildingUnlocked*>(msg);
		if (isBuildingUnlocked(*unlMsg->edificio_))
			send(&BuildingUnlocked(BUILDING_UNLOCKED, unlMsg->edificio_));
		else 
			send(&BuildingNotUnlocked(BUILDING_NOT_UNLOCKED, unlMsg->edificio_));

		break;
	}
	case COLLEXT_ELECTRIX_TAX:
		taxCollect(ELECTRIC_TAX);
		break;
	case COLLEXT_MAINTEINANCE_TAX:
		taxCollect(MAINTENANCE_TAX);
		break;

	}
}

bool BureauCrazyManager::isBuildingUnlocked(const Edificio & building)
{
	std::list<Edificio>::iterator findIter = std::find(unlockedBuildings_.begin(), unlockedBuildings_.end(),building);

	return findIter != unlockedBuildings_.end();
}

void BureauCrazyManager::setActualMoney(float f)
{
	actualMoney_ += f;
	textDinero_->setText(std::to_string((int)actualMoney_) + " $");
	infoDinero_->setText("Dinero actual: " + std::to_string((int)actualMoney_) + " $");
}



