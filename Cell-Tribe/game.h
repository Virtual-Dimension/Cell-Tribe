#pragma once
#include <cmath>
#include <bitset>
#include <stack>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <mutex>
#include <thread>
#include "Json/CJsonObject.h"

#define SEHTRY __try
#define SEHEXCEPT __except (1) { char buf[32];sprintf(buf,"ERROR: 0X%X", GetExceptionCode());MessageBoxA(0,buf,"",MB_ICONERROR);}
typedef long long LL;

constexpr int WINDOW_WIDTH = 500;
constexpr int WINDOW_HEIGHT = 500;


constexpr int OPERATOR_SUCCESS = 0;
constexpr int OPERATOR_FAILED = -1;

constexpr double MAP_BEGIN_X = -500;
constexpr double MAP_BEGIN_Y = -500;
constexpr double MAP_END_X = 500;
constexpr double MAP_END_Y = 500;

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) :x(x), y(y) {}
	bool operator == (const Point& p) const { return abs(x - p.x) < 1e-9 && abs(x - p.x) < 1e-9; }
	bool operator != (const Point& p) const { return abs(x - p.x) > 1e-9 || abs(x - p.x) > 1e-9; }
	bool operator < (const Point& p) { return x = p.x ? y < p.y : x < p.x; }
	Point operator + (const Point& p)const { return Point(x + p.x, y + p.y); }
	Point operator - (const Point& p)const { return Point(x - p.x, y - p.y); }
	Point operator * (double d)const { return Point(x * d, y * d); }
	Point operator / (double d)const { return Point(x / d, y / d); }
	void operator += (const Point& p) { *this = *this + p; }
	void operator -= (const Point& p) { *this = *this - p; }
	void operator *= (double d) { *this = *this * d; }
	void operator /= (double d) { *this = *this / d; }
	double operator * (const Point& v)const { return x * v.x + y * v.y; }
	double operator ^ (const Point& v) const { return x * v.y - y * v.x; }
	double len() { return sqrt(x * x + y * y); }
	Point rotate(double a) { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};
struct Rect {
	Point p1, p2;
	Rect() {}
	Rect(const Point& p1, const Point& p2) :p1(p1), p2(p2) {}
	Rect(double x, double y, double w, double h) :p1(x, y), p2(x + w, y + h) {}
	double area() const {
		Point p = p2 - p1;
		return p.x < 0 || p.y < 0 ? 0 : p.x * p.y;
	}
	Rect operator & (const Rect& x) const {
		Rect ret;
		ret.p1.x = std::max(p1.x, x.p1.x);
		ret.p1.y = std::max(p1.y, x.p1.y);
		ret.p2.x = std::min(p2.x, x.p2.x);
		ret.p2.y = std::min(p2.y, x.p2.y);
		return ret;
	}
	bool InRect(const Point& p)const {
		return p.x >= p1.x && p.x <= p2.x && p.y >= p1.y && p.y <= p2.y;
	}
};
template<class T, class FX, class FY>
inline Rect GetContainRect(const std::vector<T>& v, const FX& fx, const FY& fy) {
	Rect ret(Point(INFINITY, INFINITY), Point(-INFINITY, -INFINITY));
	for (const auto& p : v) {
		ret.p1.x = std::min(ret.p1.x, fx(p)); ret.p1.y = std::min(ret.p1.y, fy(p));
		ret.p2.x = std::max(ret.p2.x, fx(p)); ret.p2.y = std::max(ret.p2.y, fy(p));
	}
	return ret;
}
inline Rect GetContainRect(const std::vector<Point>& v) {
	Rect ret(Point(INFINITY, INFINITY), Point(-INFINITY, -INFINITY));
	for (const auto& p : v) {
		ret.p1.x = std::min(ret.p1.x, p.x); ret.p1.y = std::min(ret.p1.y, p.y);
		ret.p2.x = std::max(ret.p2.x, p.x); ret.p2.y = std::max(ret.p2.y, p.y);
	}
	return ret;
}

struct Line {
	Point p1, p2;
};

struct Segment {
	Point p1, p2;
};

struct Ray {
	Point p1, p2;
};

const double PI = 3.1415926535897932384626433832795;
