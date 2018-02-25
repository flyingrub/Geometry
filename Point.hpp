#pragma once

class Point;

#include "Vector.hpp"
class Point {
    public:
        double x;
        double y;
        double z;

        Point();
        Point(double x, double y, double z);
        Point(const Point &p);
        Point projectOnLine(Point b, Point c);
        Point projectOnLine(Vector bc, Point b);
        Point projectOnPlane(Point point, Vector normal);
        Point operator*(double i);
        Point operator+(Point p);
};
