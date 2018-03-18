#pragma once
#include "Point.hpp"
#include <vector>
using namespace std;

struct Sphere {
	Point center;
	double rayon;
	Sphere(Point c, double r) {
		center = c;
		rayon = r;
	}
};

struct Cylinder {
	Point origin;
	Vector axis;
	double rayon;
    Point middle;
	Cylinder(Point o, Vector a, double r) {
		origin = o;
		axis = a;
		rayon = r;
		middle = axis.middle(origin);
	}
};

double fact(int n);
void drawPoint(Point p);
void drawPoints(Point *points, long nbPoints);
void drawLine(Point a, Point b);
void drawLine(Point a, Vector v);
void drawCurve(Point *points, long nbPoints);
void drawControlPoints(vector<Point> points);
void drawSurface(vector<vector<Point> > surface);
vector<vector<Point> > inverse(vector<vector<Point> > surface);
void randomColor();