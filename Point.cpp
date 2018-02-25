#include "Point.hpp"

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(const Point &p) {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
}

Point Point::projectOnLine(Point b, Point c) {
    Point d;
    Vector bc = Vector::FromPoint(b, c);
    Vector ba = Vector::FromPoint(b, *this);
    double norme_bd = ba.scalar(bc) / bc.norme();
    bc.normalize();
    d.x = b.x + bc.x * norme_bd;
    d.y = b.y + bc.y * norme_bd;
    d.z = b.z + bc.z * norme_bd;
    return d;
}

Point Point::projectOnLine(Vector bc, Point b) {
    Point d;
    Vector ba = Vector::FromPoint(b, *this);
    double norme_bd = ba.scalar(bc) / bc.norme();
    bc.normalize();
    d.x = b.x + bc.x * norme_bd;
    d.y = b.y + bc.y * norme_bd;
    d.z = b.z + bc.z * norme_bd;
    return d;
}

Point Point::projectOnPlane(Point a, Vector normal) {
    Point d;
    Vector ma = Vector::FromPoint(*this, a);
    double norme_da = ma.scalar(normal) / normal.norme();
    normal.normalize();
    d.x = this->x - normal.x * norme_da;
    d.y = this->y - normal.y * norme_da;
    d.z = this->z - normal.z * norme_da;
    return d;
}

Point Point::operator*(double i) {
    Point p(x,y,z);
    p.x *= i;
    p.y *= i;
    p.z *= i;
    return p;
}

Point Point::operator+(Point a) {
    Point p(x,y,z);
    p.x += a.x;
    p.y += a.y;
    p.z += a.z;
    return p;
}

