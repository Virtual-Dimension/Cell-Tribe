#include "EntityPlayerTribe.h"
#include "../EvolutionController.h"
#include "../Graph/slr.h"
#include "../MapController.h"
#include <Windows.h>
inline SLColor randColor() {
	return SLColor((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX);
}

EntityPlayerTribe::EntityPlayerTribe() :
	EntityLiving(), cellsMax(0), energyMax(0), energy(0), regeneration(0), cellRadius(0), genePoints(0),
	playerName("Player"), evolutionController(0),
	moveCD(0), propagateCD(0), status(STATUS_WAIT) {
	healthMax = 0;
	moveRange = 0;
	attackRange = 0;
	moveSpeed = 0;

	health = 5;
}

EntityPlayerTribe::EntityPlayerTribe(const std::string& name, EvolutionController* evolutioncontroller) :
	EntityLiving(), cellsMax(0), energyMax(0), energy(0), cellRadius(0), regeneration(0), genePoints(0),
	playerName(name), evolutionController(evolutioncontroller),
	moveCD(0), propagateCD(0), status(STATUS_WAIT) {
	healthMax = 0;
	moveRange = 0;
	attackRange = 0;
	moveSpeed = 0;

	health = 5;
	evolutionController->gotEvolution(0);
	beEffected(evolutionController->getEvolutionEffect(0));
	propagate();
}

EntityPlayerTribe::~EntityPlayerTribe() {}

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
	addval(regeneration);
#undef addval
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::spawn(MapController* mapController) {
	if (slObject) {
		slObject->detach();
		delete slObject;
	}
	SLDynamicPointGroup* newSLObject = new SLDynamicPointGroup();
	newSLObject->move_speed = moveSpeed;
	newSLObject->static_speed = 1.0;
	int siz = (int)cellsPoint.size();
	for (auto dypoint : cellsPoint)	delete dypoint;
	cellsPoint.clear();
	for (int i = 0; i < siz; i++) {
		SLDynamicPoint* newSLDynamicPoint = new SLDynamicPoint(getPoint(), cellRadius, 10, randColor());
		cellsPoint.push_back(newSLDynamicPoint);
		newSLObject->AddPoint(newSLDynamicPoint);
	}
	newSLObject->move(getPoint());
	slObject = newSLObject;
	return EntityLiving::spawn(mapController);
}

bool EntityPlayerTribe::isPlayer() const { return true; }

int EntityPlayerTribe::move(const Point& p) {
	if (moveCD > 0) {
		printf("In the way! %lf\n", moveCD);
		return ENTITY_MOVING;
	}
	printf("[move]my:[%.2lf, %.2lf],to:[%.2lf, %.2lf],moveDis:%.2lf\n", getPoint().x, getPoint().y, p.x, p.y, (p - getPoint()).len());
	if (getMapController()->beyond(p) || (p - getPoint()).len() > moveRange) {
		printf("Too long!\n");
		return ENTITY_MOVEOUT;
	}
	((SLDynamicPointGroup*)slObject)->move(p);
	setPoint(p);
	moveCD = 2;
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::behavior() {
	Sleep(1);
	if (cellsPoint.size() == 0) {
		health = 0;
		return ENTITY_DEAD;
	}

	if (moveCD > 0) moveCD -= getMapController()->getStick();
	if (propagateCD > 0) propagateCD -= getMapController()->getStick();

	if (slGetMouseButton(SL_MOUSE_BUTTON_RIGHT)) {
		propagate();
	}

	if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
		move(SL::GetRelativeMousePos());
	}

	// atack mode

	// use mode

	heal(regeneration * getMapController()->getStick());

	// heal


	if (((SLDynamicPointGroup*)slObject)->IsStatic()) {
		SL::CameraMove(getPoint().x + SL::GetCameraOffset().x - WINDOW_WIDTH / 2, getPoint().y + SL::GetCameraOffset().y - WINDOW_HEIGHT / 2);
	}
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

int EntityPlayerTribe::propagate() {
	if (propagateCD > 0) {
		printf("propagating!\n");
		return ENTITY_PROPAGATING;
	}
	if (slObject && !((SLDynamicPointGroup*)slObject)->IsStatic()) return ENTITY_MOVING;

	int addval = min((int)cellsPoint.size() / 2 + 1, cellsMax - (int)cellsPoint.size());
	if (addval <= 0) return ENTITY_TOOMANY;
	Point newPoint = getPoint();
	std::list < SLDynamicPoint* >::iterator it = cellsPoint.begin();
	for (int i = 0; i < addval; i++) {
		if (it != cellsPoint.end()) newPoint = (*it)->GetPos();
		SLDynamicPoint* newSLDynamicPoint = new SLDynamicPoint(newPoint, cellRadius, 10, randColor());
		cellsPoint.push_back(newSLDynamicPoint);
		if (slObject) ((SLDynamicPointGroup*)slObject)->AddPoint(newSLDynamicPoint);
	}
	if (slObject)((SLDynamicPointGroup*)slObject)->move(getPoint());
	propagateCD = 2;
	return OPERATOR_SUCCESS;
}
