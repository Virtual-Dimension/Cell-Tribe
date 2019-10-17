#include "EntityPlayerTribe.h"

EntityPlayerTribe::EntityPlayerTribe() :
	EntityLiving(),
	cellsMax(0), energyMax(0), energy(0), status(STATUS_WAIT),
	genePoints(0), playerName("Player"), evolutionController(0) {
	healthMax = 0;
	moveRange = 0;
	attackRange = 0;
	moveSpeed = 0;

	health = 5;
}

EntityPlayerTribe::EntityPlayerTribe(const std::string& name) :
	EntityLiving(),
	energyMax(0), energy(0), status(STATUS_WAIT),
	genePoints(0), playerName(name), evolutionController(0) {
	healthMax = 0;
	moveRange = 0;
	attackRange = 0;
	moveSpeed = 0;

	health = 5;
}

EntityPlayerTribe::EntityPlayerTribe(const std::string& name, EvolutionController* evolutionController) : EntityLiving(),
energyMax(0), energy(0), status(STATUS_WAIT),
genePoints(0), playerName(name) {
	healthMax = 0;
	moveRange = 0;
	attackRange = 0;
	moveSpeed = 0;

	health = 5;
	beEffectedByEvolution(evolutionController->getEvolution(0));
}

EntityPlayerTribe::~EntityPlayerTribe() {}

int EntityPlayerTribe::addCells(const int& val) {
	for (int i = 0; i < val; i++) cellsPoint.push_back(Point(0, 0));
	return;
}

void EntityPlayerTribe::addStrength(const int& val) { atk += val; }

void EntityPlayerTribe::addEnergyMax(const int& val) { energyMax += val; }

std::string EntityPlayerTribe::getPlayerName() const { return playerName; }

void EntityPlayerTribe::beEffectedByEvolution(const Evolution& evolution) {
#define addval(str) (this->str+= evolution.str)
	addval(atk);
	addval(attackRange);
	addval(cellsMax);
	addval(energyMax);
	addval(healthMax);
	addval(moveRange);
	addval(moveSpeed);
#undef addval
	return;
}

int EntityPlayerTribe::move(const Point& p) {
	// API
	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::behavior() {
	// wait for player
	if (cellsPoint.size() == 0) {
		health = 0;
		return ENTITY_DEAD;
	}
	printf("I am %s\n", playerName.c_str());

	std::string opt;
	while (true) {
		printf("now status: %d\n", status);
		printf("now cells: %zu\n", cellsPoint.size());
		printf("now at: %.1lf, %.1lf\n", getPoint().x, getPoint().y);
		printf("input opt:");
		std::cin >> opt;
		if (opt == "wait") {
			status = STATUS_WAIT;
		}
		if (opt == "attack") {
			status = STATUS_ATTACK;
		}
		if (opt == "use") {
			status = STATUS_USE;
		}
		if (opt == "move") {
			Point p(0, 0);
			int res = sscanf_s(opt.c_str(), "%lf %lf", &p.x, &p.y);
			if ((p - getPoint()).len() > moveRange) {
				printf("failed");
			}
			else {
				setPoint(p);
				printf("move!");
			}
		}
		if (opt == "forge") {
			printf("no funtion!");
		}
		if (opt == "add") {
			addCells(1);
		}
		if (opt == "list") {
			Point p;
			for (int i = 0; i < getMapController()->getList().size(); i++) {
				p = getMapController()->getList()[i]->getPoint();
				printf("%s : %.1lf , %.1lf", typeid(getMapController()->getList()[i]).name(), p.x, p.y);
			}
		}
		if (opt == "exit") {
			break;
		}
	}

	return OPERATOR_SUCCESS;
}

int EntityPlayerTribe::attack(EntityLiving* other) {
	// other->beAttacked(this, atk);
	return OPERATOR_SUCCESS;
}


int EntityPlayerTribe::inRange(const Point& p) const {
	for (const auto& cpoint : cellsPoint)
		if (abs(cpoint.x - p.x) < 1 && abs(cpoint.y - p.y) < 1) return 1;
	return abs(getPoint().x - p.x) < 1 && abs(getPoint().y - p.y) < 1;
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
