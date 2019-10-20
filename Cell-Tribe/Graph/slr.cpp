#include "slr.h"

void SLObject::draw() {}
void SLObject::update(double dt) {}
void SLObject::attach() {
	SL::AddObject(this);
}
void SLObject::detach() {
	SL::RemoveObject(this);
}

SLColor::SLColor(double r, double g, double b, double a)
	:r(r), g(g), b(b), a(a) {}

double random(double l, double r) {
	return ((double)rand() / RAND_MAX) * (r - l) + l;
}

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
	SLUpdateCallBack update;
	bool window;
	thread slthread;
	list<SLObject*>list_obj;
	mutex mtx_list_obj;
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
	void AddObject(SLObject* p) {
		mtx_list_obj.lock();
		list_obj.push_back(p);
		mtx_list_obj.unlock();
	}
	void RemoveObject(SLObject* p) {
		mtx_list_obj.lock();
		list_obj.remove(p);
		mtx_list_obj.unlock();
	}
	void StartThread(int WINDOW_WIDTH, int WINDOW_HEIGHT) {
		thread t(WindowThread, WINDOW_WIDTH, WINDOW_HEIGHT);
		slthread.swap(t);
	}
	void Wait() {
		slthread.join();
	}
	void SetUpdateCallBack(SLUpdateCallBack f) {
		update = f;
	}
	bool IsWindowShowed() {
		return window;
	}
}



SLCircle::SLCircle(const Point& p, double r, int num, const SLColor& c_fill, const SLColor& c_line)
	:p(p), r(r), num(num), color_fill(c_fill), color_line(c_line) {}
void SLCircle::draw() {
	slSetForeColor(color_fill);
	slCircleFill(p.x, p.y, r, num);
	slSetForeColor(color_line);
	slCircleOutline(p.x, p.y, r, num);
}



SLRectangle::SLRectangle(const Point& p, double w, int h, const SLColor& c_fill, const SLColor& c_line)
	:p(p), w(w), h(h), color_fill(c_fill), color_line(c_line) {}
void SLRectangle::draw() {
	slSetForeColor(color_fill);
	slRectangleFill(p.x + w / 2, p.y + h / 2, w, h);
	slSetForeColor(color_line);
	slRectangleOutline(p.x + w / 2, p.y + h / 2, w, h);
}


SLCircleRef::SLCircleRef(const Point& p, double r, int num, const SLColor& c_fill, const SLColor& c_line)
	:p(p), r(r), num(num), color_fill(c_fill), color_line(c_line) {}
void SLCircleRef::draw() {
	slSetForeColor(color_fill);
	slCircleFill(p.x, p.y, r, num);
	slSetForeColor(color_line);
	slCircleOutline(p.x, p.y, r, num);
}



SLRectangleRef::SLRectangleRef(const Point& p, double w, int h, const SLColor& c_fill, const SLColor& c_line)
	:p(p), w(w), h(h), color_fill(c_fill), color_line(c_line) {}
void SLRectangleRef::draw() {
	slSetForeColor(color_fill);
	slRectangleFill(p.x - w / 2, p.y - h / 2, w, h);
	slSetForeColor(color_line);
	slRectangleOutline(p.x - w / 2, p.y - h / 2, w, h);
}


Point RandCirclePoint(const Point& c, double r) {
	Point p(rand() - RAND_MAX / 2, rand() - RAND_MAX / 2);
	return c + p / p.len() * r * ((double)rand() / RAND_MAX);
}


SLButton::SLButton() :rect(Point(), 0, 0, SLColor(), SLColor()) {}
SLButton::SLButton(const Point& p, double w, double h, const SLColor& fill, const SLColor& line)
	: rect(p, w, h, fill, line), color_fill(fill), color_line(line) {
}
void SLButton::OnClick(SLMouseEventCallBack f) {
	onclick = f;
}
void SLButton::SetText(const char* s) {
	text = s;
}
void SLButton::SetTextColor(const SLColor& c) {
	text_color = c;
}
void SLButton::SetColor(const SLColor& fill, const SLColor& line) {
	color_fill = fill;
	color_line = line;
}
void SLButton::draw() {
	rect.draw();
	slSetTextAlign(SL_ALIGN_CENTER);
	slSetForeColor(text_color);
	slText(rect.p.x + rect.w / 2, rect.p.y + rect.h / 2, text.c_str());
}
void SLButton::update(double dt) {
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



Bezier3::Bezier3() {}
Bezier3::Bezier3(const Point& s, const Point& e) :s(e), e(e) {}
void Bezier3::SetSE(const Point& s, const Point& e) {
	this->s = s;
	this->e = e;
}
void Bezier3::rand() {
	double len1 = (::rand() % (int)(((e - s).len() * 0.3) + 1));
	double len2 = (::rand() % (int)(((e - s).len() * 0.3) + 1));
	Point m = (e + s) / 2;
	if (::rand() & 1) {
		p1 = (e - s).rotate(PI / 2 * random(0.6, 1.4));
		p1 = m + p1 / p1.len() * len1;
		p2 = (s - e).rotate(PI / 2 * random(0.6, 1.4));
		p2 = m + p2 / p2.len() * len2;
	}
	else {
		p1 = (s - e).rotate(PI / 2 * random(0.6, 1.4));
		p1 = m + p1 / p1.len() * len1;
		p2 = (e - s).rotate(PI / 2 * random(0.6, 1.4));
		p2 = m + p2 / p2.len() * len2;
	}
}
Point Bezier3::GetPoint(double t) {
	return s * pow3(1 - t) + p1 * 3 * t * pow2(1 - t) + p2 * 3 * pow2(t) * (1 - t) + e * pow3(t);
}
Point Bezier3::GetS() {
	return s;
}
Point Bezier3::GetE() {
	return e;
}



SLDynamicPoint::SLDynamicPoint() :c(Point(), 0, 0, SLColor(), SLColor()), now(1) {}
SLDynamicPoint::SLDynamicPoint(const Point& p, double r, int num, const SLColor& col) : c(p, r, num, col, col), now(1) {}
void SLDynamicPoint::SetGoal(const Point& p) {
	bzr.SetSE(c.p, p);
	bzr.rand();
	now = 0;
}
void SLDynamicPoint::ChangeGoal(const Point& p) {
	bzr.SetSE(bzr.GetS(), p);
}
double SLDynamicPoint::GetNow() {
	return now;
}
Point SLDynamicPoint::GetGoal() {
	return bzr.GetE();
}
Point SLDynamicPoint::GetPos() {
	return c.p;
}
void SLDynamicPoint::move(double len) {
	now += len / (bzr.GetE() - bzr.GetS()).len();
	now = min(now, 1.0);
	c.p = bzr.GetPoint(now);
}
void SLDynamicPoint::draw() {
	return c.draw();
}



SLDynamicPointGroup::SLDynamicPointGroup() :move_speed(0), static_speed(0), flag_static(0) {}
void SLDynamicPointGroup::AddPoint(SLDynamicPoint* p) {
	lp.push_back(p);
}
void SLDynamicPointGroup::RemovePoint(SLDynamicPoint* p) {
	lp.remove(p);
}
void SLDynamicPointGroup::move(const Point& mp) {
	flag_static = 0;
	pos_static = mp;
	for (auto p : lp) p->SetGoal(RandCirclePoint(mp, 20));
}
void SLDynamicPointGroup::spread() {
	flag_static = 0;
	for (auto& p : lp)
		p->SetGoal(RandCirclePoint(p->GetPos(), 500));
}
void SLDynamicPointGroup::draw() {
	for (auto p : lp)
		p->draw();
}
void SLDynamicPointGroup::update(double t) {
	if (flag_static) {
		for (auto& p : lp)
			if (p->GetNow() == 1)
				p->SetGoal(RandCirclePoint(p->GetPos(), 20));
			else if ((p->GetPos() - pos_static).len() > 50)
				p->SetGoal(pos_static);
	}
	else {
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