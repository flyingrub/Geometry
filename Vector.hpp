#pragma once

class Vector;

#include "Point.hpp"
class Vector {
    public:
        double x;
        double y;
        double z;

        Vector();
        Vector(double x, double y, double z);
        Vector(const Vector &v);
        static Vector FromPoint(Point a, Point b);
        double norme() const;
        void normalize();
        double scalar(const Vector v) const;
        Vector vectoriel(const Vector v) const;
        double angle(const Vector v) const;
        void print();
};
