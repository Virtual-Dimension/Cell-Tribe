
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

class BaseTribe;
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
	virtual void onPickedup() {
		pickedup = 1;
		return;
	}
	virtual void onUsing() {
		used = 1;
		return;
	}
};

const int OPERATOR_SUCCESS = 0;
const int TRIBE_DEAD = -1;

class BaseTribe {
private:
	int death;
protected:
	int amount;
	int strength;
	Point point;
	BaseTribe() : amount(0), death(0), strength(0), point() {}
	~BaseTribe() {}
public:
	// behavior
	int run() {
		if (amount <= 0) death = 1;
		if (death) return TRIBE_DEAD;

		int bh_res = behavior();
		if (bh_res != OPERATOR_SUCCESS) return bh_res;
		// more_opt
		return OPERATOR_SUCCESS;
	}
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
	virtual int forage() {
		return OPERATOR_SUCCESS;
	}
	// propagate
	virtual int propagate() {
		return OPERATOR_SUCCESS;
	}
	int setDeath() { death = 1; }
	int getDeath() const { return death; }
	int getAmount() const { return amount; }
	long long calcForce() const { return 1LL * amount * strength; }
};

const int STATUS_WAIT = 0;

class PlayerTribe : public BaseTribe {
	int energyMax;
	int energy;
public:
	int status;

	PlayerTribe() : BaseTribe(), energyMax(0), energy(0), status(STATUS_WAIT) {}
	~PlayerTribe() {}
	// behavior
	virtual int behavior() override final{
		// wait for player
		return OPERATOR_SUCCESS;
	}
	// attack
	virtual int attack(BaseTribe* other) override final {
		long long damage = calcForce() / (1LL * other->getAmount() + 1) + 1;
		return OPERATOR_SUCCESS;
	}
	// forage
	virtual int forage() override final {
		return OPERATOR_SUCCESS;
	}
};

int main() {




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