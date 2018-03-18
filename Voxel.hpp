#pragma once
class Voxel;

#include "Point.hpp"
#include <vector>
#include "Utils.hpp"

using namespace std;

class Voxel {
    private:
        vector<Point> points;
        Point center;
        double size;
        void displaySphereRecurs(Point centre, double rayon, int resolution, int currentRes);
        void displayCylinderRecus(Point origin, Vector axis, double rayon, int resolution, int currentRes);
        void displayIntersectionRec(Sphere s, Cylinder c, int res, int currentRes);
        void displayUnionRec(Sphere s, Cylinder c, int res, int currentRes);
        void displaySoustractionRec(Sphere s, Cylinder c, int res, int currentRes);

    public:
        Voxel(Point center, double size);
        vector<Voxel> divide();
        Point getCenter();
        double getSize();
        void display();

        bool intersectSphere(Point center, double rayon);
        static void displaySphere(Point centre, double rayon, int resolution);

        bool intersectCylinder(Point origin, Vector axis, double rayon);
        static void displayCylinder(Point origin, Vector axis, double rayon, int resolution);

        static void displayIntersection(Sphere s, Cylinder c, int resolution);
        static void displayUnion(Sphere s, Cylinder c, int resolution);
        static void displaySoustraction(Sphere s, Cylinder c, int resolution);

};
