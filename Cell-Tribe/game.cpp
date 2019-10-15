
#pragma region Header
#include <cmath>
#include <bitset>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#pragma endregion

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) :x(x), y(y) {}
	bool operator < (const Point& p) { return x = p.x ? y < p.y : x < p.x; }
	Point operator + (const Point& p)const { return Point(x + p.x, y + p.y); }
	Point operator - (const Point& p)const { return Point(x - p.x, y - p.y); }
	Point operator * (double d)const { return Point(x * d, y * d); }
	Point operator / (double d)const { return Point(x / d, y / d); }
	Point operator += (const Point& p) { *this = *this + p; }
	Point operator -= (const Point& p) { *this = *this - p; }
	Point operator *= (double d) { *this = *this * d; }
	Point operator /= (double d) { *this = *this / d; }
	double operator * (const Point& v)const { return x * v.x + y * v.y; }
	double operator ^ (const Point& v) const { return x * v.y - y * v.x; }
	double len() { return sqrt(x * x + y * y); }
};
const int OPERATOR_SUCCESS = 0;

const int MAP_BEGIN_X = -500;
const int MAP_BEGIN_Y = -500;
const int MAP_END_X = 500;
const int MAP_END_Y = 500;

class BaseEntity;

class MapController {
	struct Key {
		BaseEntity* entity;
		Key* pre, * nxt;
		Key() : entity(), pre(0), nxt(0) {}
	};
	Key map_first;
public:
	MapController() : map_first() {}
	~MapController() {
		// delete
	}
	void push(BaseEntity* entity) {
		Key* lastKey = new Key(map_first);
		lastKey->pre = &map_first;
		map_first.entity = entity, map_first.nxt = lastKey;
		return;
	}
	std::vector < BaseEntity* > get(Point x) {
		//
	}
};

class Item {
private:
	int pickedup;
	int used;
protected:
	Point point;
public:
	Item() : pickedup(0), used(0), point() {}
	Item(const Point& p) : pickedup(0), used(0), point(p) {}
	~Item() {}
	Point getPoint() const {
		return point;
	}
	void setPoint(const Point& p) {
		point = p;
		return;
	}
	virtual int onPickedup(BaseEntity* tribe) {
		pickedup = 1;
		return OPERATOR_SUCCESS;
	}
	virtual int onUsing(BaseEntity* tribe) {
		used = 1;
		return OPERATOR_SUCCESS;
	}
	virtual int onDropped(BaseEntity* tribe) {
		return OPERATOR_SUCCESS;
	}
} apple;

const int TRIBE_DEAD = -1;

template < size_t size >
class ItemManage {
protected:
	Item* items[size];
public:
	ItemManage() : items{ 0 } {}
	Item* getItem(const size_t& id) { return items[id]; }
	Item* operator [] (const size_t& id) { return getItem(id); }
	/*int pushItem(Item* item) {
		item->onPickedup();
	}*/
};

class BaseEntity {
protected:
	Point point;
	int death;
	int setDeath() { death = 1; }
	int setPoint() { death = 1; }
public:
	BaseEntity() : death(0) {}
	~BaseEntity() {}
	virtual int run() = 0;
	int getDeath() const { return death; }
	Point getPoint() const { return point; }

};

class BaseTribe : public BaseEntity {
protected:
	int amount;
	int strength;
	Point point;
	BaseTribe() : BaseEntity(), amount(0), strength(0), point() {}
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
	virtual void beAttacked(BaseTribe* other, int damage) {
		amount -= damage;
		if (amount <= 0) death = 1;
		return;
	}
	// forage
	virtual int forage() { return OPERATOR_SUCCESS; }
	// propagate
	virtual int propagate() { return OPERATOR_SUCCESS; }


	int getAmount() const { return amount; }
	long long calcForce() const { return 1LL * amount * strength; }
};

const int STATUS_WAIT = 0;

class PlayerTribe : public BaseTribe {
	int energyMax;
	int energy;
	ItemManage < 64U > pack;
public:
	int status;

	PlayerTribe() : BaseTribe(), energyMax(0), energy(0), status(STATUS_WAIT) {}
	~PlayerTribe() {}

	void addAmount(const int& val) {
		amount += val;
		return;
	}

	virtual int move(const Point& p) override final {
		return OPERATOR_SUCCESS;
	}
	virtual int behavior() override final {
		// wait for player
		printf("There are %d cells.", amount);
		printf("OPT:");
		std::string opt;
		if (opt == "attack") {

		}
		if (opt == "")
			return OPERATOR_SUCCESS;
	}
	virtual int attack(BaseTribe* other) override final {
		long long damage = calcForce() / (1LL * other->getAmount() + 1) + 1;
		other->beAttacked(this, damage);
		return OPERATOR_SUCCESS;
	}
	virtual int forage() override final {
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