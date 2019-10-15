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
typedef long long LL;

constexpr int OPERATOR_SUCCESS = 0;

constexpr int MAP_BEGIN_X = -500;
constexpr int MAP_BEGIN_Y = -500;
constexpr int MAP_END_X = 500;
constexpr int MAP_END_Y = 500;

constexpr int TRIBE_DEAD = -1;
constexpr int ITEMMANAGER_FULL = -2;

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