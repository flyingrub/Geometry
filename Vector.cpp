#include "Vector.hpp"
#include <iostream>
#include <cmath>

#define PI 3.14159265

using namespace std;

Vector::Vector() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector::Vector(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const Vector &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

double Vector::norme() const {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vector::normalize() {
    double n = this->norme();
    this->x = this->x / n;
    this->y = this->y / n;
    this->z = this->z / n;
}

double Vector::scalar(const Vector v) const {
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector Vector::vectoriel(const Vector v) const {
    double x, y, z;
    x = this->y * v.z - this->z * v.y;
    y = this->z * v.x - this->x * v.z;
    z = this->x * v.y - this->y * v.x;
    Vector res(x, y, z);
    return res;
}

double Vector::angle(const Vector v) const {
    double scalar = this->scalar(v);
    double angle = scalar / (this->norme() * v.norme());
    return  acos(angle) * 180.0 / PI;
}

void Vector::print() {
    cout << x << " " << y << " " << z << endl;
}

Vector Vector::FromPoint(Point a, Point b) {
    Vector res;
    res.x = b.x - a.x;
    res.y = b.y - a.y;
    res.z = b.z - a.z;
    return res;
}

Point Vector::middle(Point p) {
    Point res;
    res.x = p.x + this->x / 2;
    res.y = p.y + this->y / 2;
    res.z = p.z + this->z / 2;
    return res;
}

// int main(int argc, char **argv) {
//     Vector *v = new Vector(1,2,3);
//     Vector v2(*v);
//     v2.print();
//     cout << v2.norme() << endl;
//     v2.normalize();
//     v2.print();
//     Vector v3 = v->vectoriel(v2);
//     v3.print();
//     cout << v->angle(v2) << endl;

// }