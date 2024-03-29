#include "EntityPlayerTribe.h"
#include "../EvolutionController.h"
#include "../MapController.h"

EntityPlayerTribe::EntityPlayerTribe() :
	EntityBaseTribe(), genePoints(0), playerName("Player"), evolutionController(0),
	status(STATUS_WAIT), moveNeed(0), propagateNeed(0), attackNeed(0) {}

EntityPlayerTribe::EntityPlayerTribe(const std::string& name, EvolutionController* evolutioncontroller) :
	EntityBaseTribe(), genePoints(0), playerName(name), evolutionController(evolutioncontroller),
	status(STATUS_WAIT), moveNeed(0), propagateNeed(0), attackNeed(0) {
	evolutionController->gotEvolution(0);
	beEffected(evolutionController->getEvolutionEffect(0));
	health = 5.0;
	propagate();
}

EntityPlayerTribe::~EntityPlayerTribe() {}

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
	addval(moveNeed);
	addval(propagateNeed);
	addval(attackNeed);
#undef addval
	return OPERATOR_SUCCESS;
}

bool EntityPlayerTribe::isPlayer() const { return true; }

bool EntityPlayerTribe::needEnergy() const { return true; }

int EntityPlayerTribe::behavior() {
	int baseRes = EntityBaseTribe::behavior();
	if (baseRes < 0) return baseRes;

	if (slGetMouseButton(SL_MOUSE_BUTTON_RIGHT)) {
		propagate();
	}
	if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
		move(SL::GetRelativeMousePos());
	}
	if (slGetKey('1')) {
		status |= STATUS_ATTACK;
	}
	else {
		status &= (~STATUS_ATTACK);
	}
	if (slGetKey('2')) {
		status |= STATUS_USE;
	}
	else {
		status &= (~STATUS_USE);
	}
	if (slGetKey('3')) {
		printf("Energy : %.1lf/%.1lf \n", energy, energyMax);
	}
	if (slGetKey('4')) {
		status |= STATUS_SHOW;
		showAttackRange();
	}
	else {
		status &= (~STATUS_SHOW);
	}
	if (((SLDynamicPointGroup*)slObject)->IsStatic()) {
		SL::CameraMove(getPoint().x + SL::GetCameraOffset().x - WINDOW_WIDTH / 2, getPoint().y + SL::GetCameraOffset().y - WINDOW_HEIGHT / 2);
	}
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::interact(Entity* entity) {
	if ((status & STATUS_SHOW) && entity->canBeAttacked()) {
		((EntityLiving*)entity)->showAttackRange();
	}
	if ((status & STATUS_USE) && entity->canBeUsed()) {
		for (auto cell : cellsPoint) {
			if (entity->inRange(cell.point->GetPos(), cellRadius)) {
				entity->beUsed(this);
				return ITEM_USED;
			}
		}
	}
	if ((status & STATUS_ATTACK) && entity->canBeAttacked()) {
		for (auto cell : cellsPoint) {
			if (entity->inRange(cell.point->GetPos(), attackRange)) {
				attack((EntityLiving*)entity);
				return ENTITY_ATTACKED;
			}
		}
	}
	return OPERATOR_SUCCESS;
}
