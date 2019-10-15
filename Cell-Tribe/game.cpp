
#pragma region Header
#include "game.h"
#include "BaseEntity.h"
#include "Item.h"
#include "ItemManager.h"

#define SEHTRY __try
#define SEHEXCEPT __except (1) { char buf[32];sprintf(buf,"ERROR: 0X%X", GetExceptionCode());MessageBoxA(0,buf,"",MB_ICONERROR);}
#pragma endregion


class BaseTribe : public BaseEntity {
protected:
	LL amount, strength;
	std::vector < Point > cellsPoint;
	BaseTribe() : BaseEntity(), amount(0), strength(0) {}
	~BaseTribe() {}
public:
	virtual int run() override final {
		if (amount <= 0) death = 1;
		if (death) return TRIBE_DEAD;

		int bh_res = behavior();
		if (bh_res != OPERATOR_SUCCESS) return bh_res;

		// more_opt
		return OPERATOR_SUCCESS;
	}
	// behavior

	virtual int behavior() = 0;
	// move
	virtual int move(const Point&) = 0;
	// attack
	virtual int attack(BaseTribe*) = 0;
	// be attacked
	virtual void beAttacked(BaseTribe* other, LL damage) {
		amount -= damage;
		if (amount <= 0) death = 1;
		return;
	}
	// forage
	virtual int forage() { return OPERATOR_SUCCESS; }
	// propagate
	virtual int propagate() { return OPERATOR_SUCCESS; }

	virtual int inRange(const Point& p) const override {
		for (const auto& cpoint : cellsPoint)
			if (abs(cpoint.x - p.x) < 1 && abs(cpoint.y - p.y) < 1) return 1;
		return abs(point.x - p.x) < 1 && abs(point.y - p.y) < 1;
	}

	LL getAmount() const { return amount; }
	LL calcForce() const { return 1LL * amount * strength; }
};

const int STATUS_WAIT = 0;

class PlayerTribe final : public BaseTribe {
	int energyMax, energy;
	ItemManager pack;
public:
	int status;

	PlayerTribe() : BaseTribe(), energyMax(0), energy(0), status(STATUS_WAIT), pack(64) {}
	~PlayerTribe() {}

	void addAmount(const int& val) { amount += val; }

	virtual int move(const Point& p) override {
		// API
		return OPERATOR_SUCCESS;
	}
	virtual int behavior() override {
		// wait for player
		printf("There are %lld cells.", amount);
		printf("OPT:");
		std::string opt;
		std::cin >> opt;
		if (opt == "attack") {

		}
		if (opt == "forge") {

		}
		return OPERATOR_SUCCESS;
	}
	virtual int attack(BaseTribe* other) override {
		LL damage = calcForce() / (other->getAmount() + 1) + 1;
		other->beAttacked(this, damage);
		return OPERATOR_SUCCESS;
	}
	virtual int forage() override {
		return OPERATOR_SUCCESS;
	}
	/*int pickupItem(Item* item) {
		return pack.pushItem(item);
	}*/
} player;

int main() {
	player.addAmount(10);

	player.run();



	return 0;
}

/*
控制单位：种群
	----个体：胞体
	----属性：
		----个数
		----强度（单个个体）
		----能量
	----显示：粒子效果
	----行为：
		----移动
		----攻击
		----觅食，吞噬
			----获取能量，基因点数
		----繁殖：
			----消耗能量，增加个体数量
			----概率突变：
				----有利变异：
				----不利变异：消耗基因点数退化
	----进化：
		----消耗基因点数进行进化
地图：
	----显示各种群
	----一些物品
		----食物

*/