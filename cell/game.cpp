
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
using namespace std;
#define INF ((int)0x3F3F3F3F)
#define FINF ((int)0xC0C0C0C0)
#define llINF 0x3F3F3F3F3F3F3F3FLL
#define llFINF 0xC0C0C0C0C0C0C0C0LL
typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UINT;
#pragma endregion


#define GENE_PRE_DNA 32
#define DNA_PRE_CHROMOSOME 32
#define CHROMOSOME_PRE_ENTITY 32
#define RANDOM_MAX 0x3FFFFFFF
int random() {
	return rand() << 15 | rand();
}
bool random(double p) {// rand a bool with p
	return rand() < RANDOM_MAX * p;
}
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
class DNA {
	bitset<GENE_PRE_DNA>x, y;
public:
	DNA() {}
	int count() const {
		return (x | y).count();
	}
	bool operator [] (int pos) const {
		return x[pos] | y[pos];
	}
	void mutation() {
		if (rand() & 1)x[rand() % 32].flip();
		else y[rand() % 32].flip();
	}
	DNA operator + (const DNA& d) const {
		DNA ret;
		if (rand() & 1) {
			ret.x = x;
			ret.y = d.y;
		}
		else {
			ret.y = y;
			ret.x = d.x;
		}
		return ret;
	}
};
class Entity;
class Chromo {
protected:
	DNA dna[DNA_PRE_CHROMOSOME];
protected:
	virtual void inherit(Chromo* c, double p_mutation) {
		for (int i = 0; i < DNA_PRE_CHROMOSOME; i++) {
			dna[i] = c->dna[i];
			while (random(p_mutation))dna[i].mutation();
		}
	};
	virtual void inherit(Chromo* a, Chromo* b, double p_mutation) {
		for (int i = 0; i < DNA_PRE_CHROMOSOME; i++) {
			dna[i] = a->dna[i] + b->dna[i];
			while (random(p_mutation))dna[i].mutation();
		}
	};
public:
	Chromo() {}
	const DNA& operator [] (int pos) {
		return dna[pos];
	}
	virtual void OnBirth(Entity* e) = 0;
	virtual void Behavior(Entity* e, int t) = 0;
	virtual Chromo* propagate(double p_mutation) = 0;
	virtual Chromo* propagate(Chromo* c, double p_mutation) = 0;
};
#define DEFAULT_PROPAGATE(CLASS)\
virtual Chromo* propagate(double p_mutation)override {\
	CLASS* ret = new CLASS();\
	ret->inherit(this, p_mutation);\
	return ret;\
}\
virtual Chromo* propagate(Chromo* c, double p_mutation) override {\
	CLASS* ret = new CLASS();\
	ret->inherit(this, c, p_mutation);\
	return ret;\
}
class Entity {
	Chromo* vc[CHROMOSOME_PRE_ENTITY];
	int chromo_cnt;
	int timer;
	_declspec(property(get = get_timer))int timer;
public:
	Point pos;
	int health;
	set<pair<int, Point>>move_pos;
public:
	Entity() :health(0), chromo_cnt(0), vc() {}
	~Entity() {
		for (int i = 0; i < chromo_cnt; i++)
			delete vc[i];
	}
	int get_timer() {
		return timer;
	}
	void update(int t) {
		++timer;
		for (int i = 0; i < chromo_cnt; i++) {
			vc[i]->Behavior(this, t);
		}
	}
	void AddChromo(Chromo* c) {
		vc[chromo_cnt++] = c;
		c->OnBirth(this);
	}
	Entity* propagate(double p_mutation) {
		Entity* ret = new Entity();
		ret->chromo_cnt = chromo_cnt;
		for (int i = 0; i < chromo_cnt; i++) {
			ret->vc[i] = vc[i]->propagate(p_mutation);
		}
		for (int i = 0; i < chromo_cnt; i++) {
			ret->vc[i]->OnBirth(ret);
		}
		return ret;
	}
	Entity* propagate(const Entity& e, double p_mutation) {
		_ASSERTE(chromo_cnt == e.chromo_cnt);
		Entity* ret = new Entity();
		ret->chromo_cnt = chromo_cnt;
		for (int i = 0; i < chromo_cnt; i++) {
			ret->vc[i] = vc[i]->propagate(e.vc[i], p_mutation);
		}
		for (int i = 0; i < chromo_cnt; i++) {
			ret->vc[i]->OnBirth(ret);
		}
		return ret;
	}
};

class Chromo_Health :public Chromo {
public:
	Chromo_Health() {}
	virtual void OnBirth(Entity* e) override {
		for (int i = 0; i < DNA_PRE_CHROMOSOME; i++) {
			e->health += dna[i].count();
		}
	}
	virtual void Behavior(Entity* e, int t) override {}
	//use default propagate
	DEFAULT_PROPAGATE(Chromo_Health);
};
class Chromo_Move :public Chromo {
public:
	Chromo_Move() {}
	virtual void OnBirth(Entity* e) override {}
	virtual void Behavior(Entity* e, int t) override {
		if (e->move_pos.empty())return;
		int speed = 0;
		for (int i = 0; i < DNA_PRE_CHROMOSOME; i++)
			speed += dna[i].count();
		Point goal = e->move_pos.begin()->second;
		Point v = goal - e->pos;
		v = v * speed / v.len();

		Point px = e->pos + v;

		if ((px.x - goal.x > 0) == (e->pos.x - goal.x < 0)
			&& (px.y - goal.y > 0) == (e->pos.y - goal.y < 0)) {
			e->pos = goal;
			e->move_pos.erase(e->move_pos.begin());
		}
		else {
			e->pos += v;
		}
	}
	//use default propagate
	DEFAULT_PROPAGATE(Chromo_Move);
};

class Chromo_Forage :public Chromo {
public:
	Chromo_Forage() {}
	virtual void OnBirth(Entity* e) override {}
	virtual void Behavior(Entity* e, int t) override {
		if (e->move_pos.empty())return;

	}
	//use default propagate
	DEFAULT_PROPAGATE(Chromo_Forage);
};



int main() {




	return 0;
}
