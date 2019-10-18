#pragma once

#include "../game.h"
#include "sl.h"

#pragma warning( disable : 4244 )
#pragma warning( disable : 26451 )

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
	virtual void draw() {}
	virtual void update(double dt) {}
	virtual void attach() { SL::AddObject(this); }
	virtual void detach() { SL::RemoveObject(this); }
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
double Hue2RGB(double v1, double v2, double vH) {
	if (vH < 0) vH += 1;
	if (vH > 1) vH -= 1;
	if (6.0 * vH < 1) return v1 + (v2 - v1) * 6.0 * vH;
	if (2.0 * vH < 1) return v2;
	if (3.0 * vH < 2) return v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;
	return (v1);
}
SLColor HSL2RGB(double H, double S, double L, double A) {
	double R, G, B;
	double var_1, var_2;
	if (S == 0) {
		R = L * 255.0;
		G = L * 255.0;
		B = L * 255.0;
	}
	else {
		if (L < 0.5) var_2 = L * (1 + S);
		else         var_2 = (L + S) - (S * L);

		var_1 = 2.0 * L - var_2;

		R = Hue2RGB(var_1, var_2, H + (1.0 / 3.0));
		G = Hue2RGB(var_1, var_2, H);
		B = Hue2RGB(var_1, var_2, H - (1.0 / 3.0));
	}
	return SLColor(R, G, B, A);
}
void slSetForeColor(const SLColor& c) {
	return slSetForeColor(c.r, c.g, c.b, c.a);
}
namespace SL {
	std::list<SLObject*>list_obj;
	std::mutex mtx_list_obj;
	std::thread slthread;
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
				p->update(dt);
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
		std::thread t(WindowThread, WINDOW_WIDTH, WINDOW_HEIGHT);
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

class SLPicture {

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
Point RandCirclePoint(const Point& c, double r) {
	Point p(rand() - RAND_MAX / 2, rand() - RAND_MAX / 2);
	return c + p / p.len() * r * ((double)rand() / RAND_MAX);
}
typedef void(*SLMouseEventCallBack)(double x, double y);
class SLButton :public SLObject {
	SLRectangle rect;
	SLMouseEventCallBack onclick;
	bool lbtn;
	std::string text;
	SLColor text_color;
	SLColor color_fill, color_line;
public:
	SLButton() : rect(Point(), 0, 0, SLColor(), SLColor()), lbtn(0), onclick(0) {}
	SLButton(const Point& p, double w, double h, const SLColor& fill, const SLColor& line)
		: rect(p, w, h, fill, line), color_fill(fill), color_line(line), lbtn(0), onclick(0) {	}
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
	virtual void update(double dt) override {
		double mx = slGetMouseX(), my = slGetMouseY();
		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT)) {
			if (mx >= rect.p.x && my >= rect.p.y
				&& mx <= rect.p.x + rect.w && my <= rect.p.y + rect.h) {
				lbtn = 1;
				rect.color_fill = color_fill;
				rect.color_fill.a = std::max(rect.color_fill.a - 0.3, 0.1);
				rect.color_line = color_line;
				rect.color_line.a = std::max(rect.color_line.a - 0.3, 0.1);
			}
		}
		else {
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
