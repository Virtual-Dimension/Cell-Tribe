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

const double PI = 3.1415926535897932384626433832795;
