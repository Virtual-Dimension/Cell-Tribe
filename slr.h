#pragma once
#include "sl.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;
class SLObject;
namespace SL {
	typedef void(*SLUpdateCallBack)(double);
	void WindowThread(int WINDOW_WIDTH, int WINDOW_HEIGHT);
	inline void AddObject(SLObject* p);
	inline void RemoveObject(SLObject* p);
	inline void StartThread(int WINDOW_WIDTH, int WINDOW_HEIGHT);
	inline void Wait();
	inline void SetUpdateCallBack(SLUpdateCallBack f);
}
class SLObject {
public:
	virtual void draw() = 0;
	virtual void update() {

	}
	void attach() {
		SL::AddObject(this);
	}
	void detach() {
		SL::RemoveObject(this);
	}
};
const double PI = 3.1415926535897932384626433832795;
struct Point {
	double x, y;
	Point() :x(0), y(0) {}
	Point(double x, double y) :x(x), y(y) {}
	bool operator == (const Point& p) const { return abs(x - p.x) < 1e-9 && abs(x - p.x) < 1e-9; }
	bool operator != (const Point& p) const { return abs(x - p.x) > 1e-9 || abs(x - p.x) > 1e-9; }
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
	Point rotate(double a) { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};
struct Line {
	Point p1, p2;
};
struct Segment {
	Point p1, p2;
};
struct Ray {
	Point p1, p2;
};
struct SLColor {
	double r, g, b, a;
	SLColor(double r = 0, double g = 0, double b = 0, double a = 0)
		:r(r), g(g), b(b), a(a) {}
};
void slSetForeColor(const SLColor& c) {
	return slSetForeColor(c.r, c.g, c.b, c.a);
}
namespace SL {
	list<SLObject*>list_obj;
	mutex mtx_list_obj;
	thread slthread;
	SLUpdateCallBack update;
	bool window;
	void WindowThread(int WINDOW_WIDTH, int WINDOW_HEIGHT) {
		slWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SIGIL", false);
		window = 1;
		//slTranslate(0, WINDOW_HEIGHT);
		//slRotate(180);
		//slSetBackColor(0.0, 0.0, 0.0);
		while (!slShouldClose()) {
			double dt = slGetDeltaTime();

			if (update)
				update(dt);

			mtx_list_obj.lock();
			for (const auto p : list_obj)
				p->draw();
			for (const auto p : list_obj)
				p->update();
			mtx_list_obj.unlock();

			slRender();
		}
		slClose();
	}
	inline void AddObject(SLObject* p) {
		mtx_list_obj.lock();
		list_obj.push_back(p);
		mtx_list_obj.unlock();
	}
	inline void RemoveObject(SLObject* p) {
		mtx_list_obj.lock();
		list_obj.remove(p);
		mtx_list_obj.unlock();
	}
	inline void StartThread(int WINDOW_WIDTH, int WINDOW_HEIGHT) {
		thread t(WindowThread, WINDOW_WIDTH, WINDOW_HEIGHT);
		slthread.swap(t);
	}
	inline void Wait() {
		slthread.join();
	}
	inline void SetUpdateCallBack(SLUpdateCallBack f) {
		update = f;
	}
}
class SLCircle :public SLObject {
public:
	Point p;
	double r;
	int num;
	SLColor color_fill;
	SLColor color_line;
public:
	SLCircle(const Point& p, double r, int num, const SLColor& c_fill, const SLColor& c_line)
		:p(p), r(r), num(num), color_fill(c_fill), color_line(c_line) {}
	virtual void draw() override {
		slSetForeColor(color_fill);
		slCircleFill(p.x, p.y, r, num);
		slSetForeColor(color_line);
		slCircleOutline(p.x, p.y, r, num);
	}
};
class SLRectangle :public SLObject {
public:
	Point p;
	double w, h;
	SLColor color_fill;
	SLColor color_line;
public:
	SLRectangle(const Point& p, double w, int h, const SLColor& c_fill, const SLColor& c_line)
		:p(p), w(w), h(h), color_fill(c_fill), color_line(c_line) {}
	virtual void draw() override {
		slSetForeColor(color_fill);
		slRectangleFill(p.x + w / 2, p.y + h / 2, w, h);
		slSetForeColor(color_line);
		slRectangleOutline(p.x + w / 2, p.y + h / 2, w, h);
	}
};

class SLCircleRef :public SLObject {
public:
	const Point& p;
	double r;
	int num;
	SLColor color_fill;
	SLColor color_line;
public:
	SLCircleRef(const Point& p, double r, int num, const SLColor& c_fill, const SLColor& c_line)
		:p(p), r(r), num(num), color_fill(c_fill), color_line(c_line) {}
	virtual void draw() override {
		slSetForeColor(color_fill);
		slCircleFill(p.x, p.y, r, num);
		slSetForeColor(color_line);
		slCircleOutline(p.x, p.y, r, num);
	}
};

class SLRectangleRef :public SLObject {
public:
	const Point& p;
	double w, h;
	SLColor color_fill;
	SLColor color_line;
public:
	SLRectangleRef(const Point& p, double w, int h, const SLColor& c_fill, const SLColor& c_line)
		:p(p), w(w), h(h), color_fill(c_fill), color_line(c_line) {}
	virtual void draw() override {
		slSetForeColor(color_fill);
		slRectangleFill(p.x - w / 2, p.y - h / 2, w, h);
		slSetForeColor(color_line);
		slRectangleOutline(p.x - w / 2, p.y - h / 2, w, h);
	}
};
typedef void(*SLMouseEventCallBack)(double x, double y);
class SLButton :public SLObject {
	SLRectangle rect;
	SLMouseEventCallBack onclick;
	bool lbtn;
	string text;
	SLColor text_color;
	SLColor color_fill, color_line;
public:
	SLButton() :rect(Point(), 0, 0, SLColor(), SLColor()) {}
	SLButton(const Point& p, double w, double h, const SLColor& fill, const SLColor& line)
		:rect(p, w, h, fill, line), color_fill(fill), color_line(line) {
	}
	void OnClick(SLMouseEventCallBack f) {
		onclick = f;
	}
	void SetText(const char* s) {
		text = s;
	}
	void SetTextColor(const SLColor& c) {
		text_color = c;
	}
	void SetColor(const SLColor& fill, const SLColor& line) {
		color_fill = fill;
		color_line = line;
	}
	virtual void draw() override {
		rect.draw();
		slSetTextAlign(SL_ALIGN_CENTER);
		slSetForeColor(text_color);
		slText(rect.p.x + rect.w / 2, rect.p.y + rect.h / 2, text.c_str());
	}
	virtual void update() override {
		double mx = slGetMouseX(), my = slGetMouseY();
		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
			if (mx >= rect.p.x && my >= rect.p.y
				&& mx <= rect.p.x + rect.w && my <= rect.p.y + rect.h) {
				lbtn = 1;
				rect.color_fill = color_fill;
				rect.color_fill.a = max(rect.color_fill.a - 0.3, 0.1);
				rect.color_line = color_line;
				rect.color_line.a = max(rect.color_line.a - 0.3, 0.1);
			}
		} else {
			if (lbtn && onclick
				&& mx >= rect.p.x && my >= rect.p.y
				&& mx <= rect.p.x + rect.w && my <= rect.p.y + rect.h) {
				onclick(mx, my);
			}
			lbtn = 0;
			rect.color_fill = color_fill;
			rect.color_line = color_line;
		}
	}
};
