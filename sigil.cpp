#include "sl.h"
#include "slr.h"
#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <set>
#include <windows.h>
#include <algorithm>

#ifndef _DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif


double random(double l, double r) {
	return ((double)rand() / RAND_MAX) * (r - l) + l;
}

using namespace std;
const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 600;
double moveTowards(double current, double target, double step) {
	double result = current + (target - current) * step;
	if (current < target && result > target) result = target;
	else if (current > target&& result < target) result = target;
	return result;
}
Point moveTowards(const Point& current, const Point& target, double step) {
	return Point(moveTowards(current.x, target.x, step), moveTowards(current.y, target.y, step));
}

class Bezier3 {
	Point s, p1, p2, e;
	static double pow2(double x) { return x * x; }
	static double pow3(double x) { return x * x * x; }
public:
	Bezier3() {}
	Bezier3(const Point& s, const Point& e) :s(e), e(e) {}
	void SetSE(const Point& s, const Point& e) {
		this->s = s;
		this->e = e;
	}
	void rand() {
		double len1 = (::rand() % (int)(((e - s).len() * 0.3) + 1));
		double len2 = (::rand() % (int)(((e - s).len() * 0.3) + 1));
		Point m = (e + s) / 2;
		if (::rand() & 1) {
			p1 = (e - s).rotate(PI / 2 * random(0.6, 1.4));
			p1 = m + p1 / p1.len() * len1;
			p2 = (s - e).rotate(PI / 2 * random(0.6, 1.4));
			p2 = m + p2 / p2.len() * len2;
		} else {
			p1 = (s - e).rotate(PI / 2 * random(0.6, 1.4));
			p1 = m + p1 / p1.len() * len1;
			p2 = (e - s).rotate(PI / 2 * random(0.6, 1.4));
			p2 = m + p2 / p2.len() * len2;
		}
	}
	Point GetPoint(double t) {
		return s * pow3(1 - t) + p1 * 3 * t * pow2(1 - t) + p2 * 3 * pow2(t) * (1 - t) + e * pow3(t);
	}
	Point GetS() {
		return s;
	}
	Point GetE() {
		return e;
	}
};
template<int N, int M>
struct Combinatorial {
	static constexpr double val = Combinatorial<N - 1, M>::val + Combinatorial<N - 1, M - 1>::val;
};
template<int N>
struct Combinatorial<N, 1> {
	static constexpr double val = N;
};
template<int N>
struct Combinatorial<N, 0> {
	static constexpr double val = 1;
};
template<int N>
struct Combinatorial<N, N> {
	static constexpr double val = 1;
};
template<size_t N>
class Bezier {
	Point p[N + 1];
public:
	Bezier() {}
	Bezier(const Point& s, const Point& e) {
		p[0] = s;
		p[N] = e;
	}
	void SetSE(const Point& s, const Point& e) {
		p[0] = s;
		p[N] = e;
	}
	void rand() {
		int x = ::rand() & 1;
		for (int i = 1; i < N; i++) {
			double len = ::rand() % ((int)(((p[N] - p[1]).len() * 0.3) + 1));
			if ((i & 1) == x) {
				p[i] = (p[N] - p[0]).rotate(PI / 2);
				p[i] = p[0] + (p[N] - p[0]) * (1.0 / N * i) + p[i] / p[i].len() * len;
			} else {
				p[i] = (p[N] - p[0]).rotate(PI * 1.5);
				p[i] = p[0] + (p[N] - p[0]) * (1.0 / N * i) + p[i] / p[i].len() * len;
			}
		}
	}
	template<size_t P>
	Point _GetPoint(double t) {
		return p[P] * pow(1 - t, N - P) * pow(t, P) * Combinatorial<N, P>::val + _GetPoint<P - 1>(t);
	}
	template<>
	Point _GetPoint<0>(double t) {
		return p[0] * pow(1 - t, N) * Combinatorial<N, 0>::val;
	}
	Point GetPoint(double t) {
		return _GetPoint<N>(t);
	}
	Point GetS() {
		return p[0];
	}
	Point GetE() {
		return p[N];
	}
};


int rand_next(int seed) {
	seed %= 32768;
	seed = seed * 1103515245 + 12345;
	return((unsigned)(seed / 65536) % 32768);
}

class SLDynamicPoint :public SLObject {
	SLCircle c;
	Bezier3 bzr;
	double now;
public:
	SLDynamicPoint() :c(Point(), 0, 0, SLColor(), SLColor()), now(1) {}
	SLDynamicPoint(const Point& p, double r, int num, const SLColor& col) :c(p, r, num, col, col), now(1) {}
	void SetGoal(const Point& p) {
		bzr.SetSE(c.p, p);
		bzr.rand();
		now = 0;
	}
	void ChangeGoal(const Point& p) {
		bzr.SetSE(bzr.GetS(), p);
	}
	double GetNow() {
		return now;
	}
	Point GetGoal() {
		return bzr.GetE();
	}
	Point GetPos() {
		return c.p;
	}
	void move(double len) {
		now += len / (bzr.GetE() - bzr.GetS()).len();
		now = min(now, 1);
		c.p = bzr.GetPoint(now);
	}
	virtual void draw() override {
		return c.draw();
	}
};

class SLDynamicPointGroup :public SLObject {
	list<SLDynamicPoint*>lp;
	bool flag_static;
	Point pos_static;
public:
	double move_speed, static_speed;
public:
	SLDynamicPointGroup() :move_speed(0), static_speed(0), flag_static(0) {}
	void AddPoint(SLDynamicPoint* p) {
		lp.push_back(p);
	}
	void RemovePoint(SLDynamicPoint* p) {
		lp.remove(p);
	}
	void move(const Point& mp) {
		flag_static = 0;
		pos_static = mp;
		for (auto p : lp) p->SetGoal(RandCirclePoint(mp, 20));
	}
	void spread() {
		flag_static = 0;
		for (auto& p : lp)
			p->SetGoal(RandCirclePoint(p->GetPos(), 500));
	}
public:
	virtual void draw() override {
		for (auto p : lp)
			p->draw();
	}
	virtual void update(double t) override {
		if (flag_static) {
			for (auto& p : lp)
				if (p->GetNow() == 1)
					p->SetGoal(RandCirclePoint(p->GetPos(), 20));
				else if ((p->GetPos() - pos_static).len() > 50)
					p->SetGoal(pos_static);
		} else {
			double pj = 0;
			for (auto p : lp)
				pj += p->GetNow();
			pj /= lp.size();
			if (pj > 0.95) {
				flag_static = 1;
			}
		}
		if (flag_static)
			for (auto p : lp) p->move(static_speed * t);
		else
			for (auto p : lp) p->move(move_speed * t);
	}
};

//class Particle :public SLObject {
//	vector<SLCircle>vc;
//public:
//	Point p;
//	double r;
//public:
//	Particle() :r(0) {
//	}
//	Particle(const Point& p, double r) {
//	}
//	void update(double t) {
//		for (auto& c : vc) {
//			double x = (c.p - p).len();
//
//		}
//	}
//	virtual void draw() override {
//
//	}
//};

const double MOVE_SPEED = 100;
const double STATIC_SPEED = 30;
vector<SLDynamicPoint*>vp;
SLDynamicPointGroup* dpg;
void update(double t) {
	//printf("%.2lf\n", 1 / t);
	static bool flag_static = 0;
	static Point pos_static;
	static double cd_spread = 0, cd_move = 0;
	cd_spread -= t;
	cd_move -= t;
	Point mp(slGetMouseX(), slGetMouseY());
	if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT) && cd_move <= 0) {
		dpg->move(mp);
	}
	if (cd_spread <= 0 && slGetMouseButton(SL_MOUSE_BUTTON_RIGHT)) {
		dpg->spread();
	}
}




SLColor Ranbow(double p, double alpha) {
	return HSL2RGB(p, 1, 0.5, alpha);
}
char s[1024];
int main(int args, char* argv[]) {
	SLDynamicPointGroup pg;
	pg.move_speed;
	GetWindowsDirectoryA(s, 1024);
	puts(s);

	SL::StartThread(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (!SL::window)Sleep(100);

	int font = slLoadFont("./ttf/white_rabbit.ttf");
	slSetFont(font, 16);
	//slText(100, 100, "123123123");


	SLButton b(Point(200, 200), 100, 50, SLColor(0.5, 0, 0, 0.5), SLColor());
	b.OnClick([](double x, double y) {puts("Click()"); });
	b.SetText("Click Here");
	b.SetTextColor(SLColor(1, 1, 1, 1));
	b.attach();


	srand(time(0));

	SL::SetUpdateCallBack(update);



	for (int i = 0; i < 500; i++) {
		vp.push_back(new SLDynamicPoint(Point(0, 0), 2, 10, Ranbow(i / 500.0, 0.3)));
	}
	random_shuffle(vp.begin(), vp.end());
	//for (auto p : vp)
	//	p->attach();

	dpg = new SLDynamicPointGroup();

	for (auto p : vp)
		dpg->AddPoint(p);

	dpg->move_speed = 100;
	dpg->static_speed = 20;
	dpg->attach();


	SL::Wait();

	return 0;
}

/*

   吊古战场
吊古兴亡感慨多
茫茫漠漠奈愁何
琵琶一曲螳螂墓
惆怅西风万里歌

天下正人无一事
鹧鸪声里白云汀
杜鹃啼鸟归来晚
芳草萋萋满地青

*/