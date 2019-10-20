#include "EntityPlayerTribe.h"
#include "../EvolutionController.h"
#include "../Graph/slr.h"
#include "../MapController.h"

EntityPlayerTribe::EntityPlayerTribe() :
	EntityLiving(), cellsMax(0), energyMax(0), energy(0), cellRadius(0), status(STATUS_WAIT), genePoints(0),
	playerName("Player"), evolutionController(0) {
	healthMax = 0;
	moveRange = 0;
	attackRange = 0;
	moveSpeed = 0;

	health = 5;
}

EntityPlayerTribe::EntityPlayerTribe(const std::string& name, EvolutionController* evolutioncontroller) :
	EntityLiving(), energyMax(0), energy(0), cellRadius(0), status(STATUS_WAIT), genePoints(0),
	playerName(name), evolutionController(evolutioncontroller) {
	healthMax = 0;
	moveRange = 0;
	attackRange = 0;
	moveSpeed = 0;

	health = 5;
	evolutionController->gotEvolution(0);
	beEffected(evolutionController->getEvolutionEffect(0));
	addCells(1);
}

EntityPlayerTribe::~EntityPlayerTribe() {}

int EntityPlayerTribe::addCells(const int& val) {
	int addval = std::min(val, cellsMax - (int)cellsPoint.size());
	for (int i = 0; i < addval; i++) {
		SLDynamicPoint* newSLDynamicPoint = new SLDynamicPoint(getPoint(), cellRadius, 10, SLColor((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 1));
		cellsPoint.push_back(newSLDynamicPoint);
		if (slObject) ((SLDynamicPointGroup*)slObject)->AddPoint(newSLDynamicPoint);
	}
	return addval <= 0 ? OPERATOR_FAILED : OPERATOR_SUCCESS;
}

void EntityPlayerTribe::addStrength(const int& val) { atk += val; }

void EntityPlayerTribe::addEnergyMax(const int& val) { energyMax += val; }

std::string EntityPlayerTribe::getPlayerName() const { return playerName; }

int EntityPlayerTribe::beEffected(const Effect& effect) {
#define addval(str) (this->str+= effect.str)
	addval(atk);
	addval(attackRange);
	addval(cellsMax);
	addval(energyMax);
	addval(healthMax);
	addval(moveRange);
	addval(moveSpeed);
	addval(cellRadius);
#undef addval
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::spawn(MapController* mapController) {
	if (slObject) {
		slObject->detach();
		delete slObject;
	}
	SLDynamicPointGroup* newSLObject = new SLDynamicPointGroup();
	int siz = cellsPoint.size();
	for (auto dypoint : cellsPoint)	delete dypoint;
	cellsPoint.clear();
	for (int i = 0; i < siz; i++) {
		SLDynamicPoint* newSLDynamicPoint = new SLDynamicPoint(getPoint(), cellRadius, 10, SLColor((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 1));
		cellsPoint.push_back(newSLDynamicPoint);
		newSLObject->AddPoint(newSLDynamicPoint);
	}
	slObject = newSLObject;
	return EntityLiving::spawn(mapController);
}

bool EntityPlayerTribe::isPlayer() const { return true; }

int EntityPlayerTribe::move(const Point& p) {
	printf("[move] my: [%.2lf, %.2lf] ,moveDis : %.2lf, moveRange : %.2lf\n", getPoint().x, getPoint().y, (p - getPoint()).len(), moveRange);
	if (getMapController()->beyond(p) || (p - getPoint()).len() > moveRange) return OPERATOR_FAILED;
	((SLDynamicPointGroup*)slObject)->move(p);
	setPoint(p);
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::behavior() {
	// wait for player
	if (cellsPoint.size() == 0) {
		health = 0;
		return ENTITY_DEAD;
	}
	//printf("I am %s\n", playerName.c_str());
	if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
		Point p = SL::GetRelativeMousePos();
		move(p);
	}
	//move
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::attack(EntityLiving* other) {
	// other->beAttacked(this, atk);
	return OPERATOR_SUCCESS;
}


int EntityPlayerTribe::inRange(const Point& p, const double& dis) const {
	for (auto dypoint : cellsPoint)
		if ((dypoint->GetPos() - p).len() < dis) return 1;
	return 0;
}

int EntityPlayerTribe::interact1(Entity* entity) {
	if ((status & STATUS_USE) && entity->canBeUsed()) {
		entity->beUsed(this);
		return ITEM_USED;
	}
	if ((status & STATUS_ATTACK) && entity->canBeAttacked()) {
		this->attack((EntityLiving*)entity);
		return ENTITY_ATTACKED;
	}
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::print() const {
	return OPERATOR_SUCCESS;
}
