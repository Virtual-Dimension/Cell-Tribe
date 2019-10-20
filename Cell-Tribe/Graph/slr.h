#pragma once
#include "sl.h"
#include "../game.h"
using namespace std;
class SLObject;
namespace SL {
	typedef void(*SLUpdateCallBack)(double);
	void WindowThread(int WINDOW_WIDTH, int WINDOW_HEIGHT);
	void AddObject(SLObject* p);
	void RemoveObject(SLObject* p);
	void StartThread(int WINDOW_WIDTH, int WINDOW_HEIGHT);
	void Wait();
	void SetUpdateCallBack(SLUpdateCallBack f);
	bool IsWindowShowed();
}
class SLObject {
public:
	virtual void draw();
	virtual void update(double dt);
	virtual void attach();
	virtual void detach();
};

struct SLColor {
	double r, g, b, a;
	SLColor(double r = 0, double g = 0, double b = 0, double a = 0);
};
double Hue2RGB(double v1, double v2, double vH);
SLColor HSL2RGB(double H, double S, double L, double A);
void slSetForeColor(const SLColor& c);
class SLCircle :public SLObject {
public:
	Point p;
	double r;
	int num;
	SLColor color_fill;
	SLColor color_line;
public:
	SLCircle(const Point& p, double r, int num, const SLColor& c_fill, const SLColor& c_line);
	virtual void draw() override;
};
class SLRectangle :public SLObject {
public:
	Point p;
	double w, h;
	SLColor color_fill;
	SLColor color_line;
public:
	SLRectangle(const Point& p, double w, int h, const SLColor& c_fill, const SLColor& c_line);
	virtual void draw() override;
};

class SLCircleRef :public SLObject {
public:
	const Point& p;
	double r;
	int num;
	SLColor color_fill;
	SLColor color_line;
public:
	SLCircleRef(const Point& p, double r, int num, const SLColor& c_fill, const SLColor& c_line);
	virtual void draw() override;
};

class SLRectangleRef :public SLObject {
public:
	const Point& p;
	double w, h;
	SLColor color_fill;
	SLColor color_line;
public:
	SLRectangleRef(const Point& p, double w, int h, const SLColor& c_fill, const SLColor& c_line);
	virtual void draw() override;
};
Point RandCirclePoint(const Point& c, double r);
typedef void(*SLMouseEventCallBack)(double x, double y);
class SLButton :public SLObject {
	SLRectangle rect;
	SLMouseEventCallBack onclick;
	bool lbtn;
	string text;
	SLColor text_color;
	SLColor color_fill, color_line;
public:
	SLButton();
	SLButton(const Point& p, double w, double h, const SLColor& fill, const SLColor& line);
	void OnClick(SLMouseEventCallBack f);
	void SetText(const char* s);
	void SetTextColor(const SLColor& c);
	void SetColor(const SLColor& fill, const SLColor& line);
	virtual void draw() override;
	virtual void update(double dt) override;
};

class Bezier3 {
	Point s, p1, p2, e;
	static double pow2(double x) { return x * x; }
	static double pow3(double x) { return x * x * x; }
public:
	Bezier3();
	Bezier3(const Point& s, const Point& e);
	void SetSE(const Point& s, const Point& e);
	void rand();
	Point GetPoint(double t);
	Point GetS();
	Point GetE();
};

class SLDynamicPoint :public SLObject {
	SLCircle c;
	Bezier3 bzr;
	double now;
public:
	SLDynamicPoint();
	SLDynamicPoint(const Point& p, double r, int num, const SLColor& col);
	void SetGoal(const Point& p);
	void ChangeGoal(const Point& p);
	double GetNow();
	Point GetGoal();
	Point GetPos();
	void move(double len);
	virtual void draw() override;
};

class SLDynamicPointGroup :public SLObject {
	list<SLDynamicPoint*>lp;
	bool flag_static;
	Point pos_static;
public:
	double move_speed, static_speed;
public:
	SLDynamicPointGroup();
	void AddPoint(SLDynamicPoint* p);
	void RemovePoint(SLDynamicPoint* p);
	void move(const Point& mp);
	void spread();
public:
	virtual void draw() override;
	virtual void update(double t) override;
};