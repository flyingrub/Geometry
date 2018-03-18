#include "Voxel.hpp"
#include <GL/glut.h>
#include <vector>
#include "Utils.hpp"
#include <stdio.h>
#include <iostream>


using namespace std;


Voxel::Voxel(Point center, double size) {
	this->size = size;
	this->center = center;
	double milength = size / 2;
	points.push_back(Point(center.x - milength, center.y - milength, center.z - milength));
	points.push_back(Point(center.x - milength, center.y + milength, center.z - milength));
	points.push_back(Point(center.x + milength, center.y + milength, center.z - milength));
	points.push_back(Point(center.x + milength, center.y - milength, center.z - milength));
	points.push_back(Point(center.x - milength, center.y - milength, center.z + milength));
	points.push_back(Point(center.x - milength, center.y + milength, center.z + milength));
	points.push_back(Point(center.x + milength, center.y + milength, center.z + milength));
	points.push_back(Point(center.x + milength, center.y - milength, center.z + milength));
}


void Voxel::display() {
	Point p1 = points[0];
	Point p2 = points[1];
	Point p3 = points[2];
	Point p4 = points[3];
	Point p5 = points[4];
	Point p6 = points[5];
	Point p7 = points[6];
	Point p8 = points[7];

	glBegin(GL_QUADS);

	glVertex3f(p4.x,p4.y,p4.z);
	glVertex3f(p3.x,p3.y,p3.z);
	glVertex3f(p2.x,p2.y,p2.z);
	glVertex3f(p1.x,p1.y,p1.z);

	glVertex3f(p5.x,p5.y,p5.z);
	glVertex3f(p6.x,p6.y,p6.z);
	glVertex3f(p7.x,p7.y,p7.z);
	glVertex3f(p8.x,p8.y,p8.z);

	glVertex3f(p1.x,p1.y,p1.z);
	glVertex3f(p5.x,p5.y,p5.z);
	glVertex3f(p6.x,p6.y,p6.z);
	glVertex3f(p2.x,p2.y,p2.z);

	glVertex3f(p6.x,p6.y,p6.z);
	glVertex3f(p2.x,p2.y,p2.z);
	glVertex3f(p3.x,p3.y,p3.z);
	glVertex3f(p7.x,p7.y,p7.z);

	glVertex3f(p3.x,p3.y,p3.z);
	glVertex3f(p7.x,p7.y,p7.z);
	glVertex3f(p8.x,p8.y,p8.z);
	glVertex3f(p4.x,p4.y,p4.z);

	glVertex3f(p8.x,p8.y,p8.z);
	glVertex3f(p4.x,p4.y,p4.z);
	glVertex3f(p1.x,p1.y,p1.z);
	glVertex3f(p5.x,p5.y,p5.z);

	glEnd();
}

vector<Voxel> Voxel::divide() {
	vector<Voxel> res;
	double size4 = size / 4;
	Point center1, center2, center3, center4,
			center5, center6, center7, center8;
	center1.x = center.x - size4;
	center1.y = center.y + size4;
	center1.z = center.z - size4;

	center2.x = center.x + size4;
	center2.y = center.y + size4;
	center2.z = center.z - size4;

	center3.x = center.x - size4;
	center3.y = center.y - size4;
	center3.z = center.z - size4;

	center4.x = center.x + size4;
	center4.y = center.y - size4;
	center4.z = center.z - size4;

	center5.x = center.x - size4;
	center5.y = center.y + size4;
	center5.z = center.z + size4;

	center6.x = center.x + size4;
	center6.y = center.y + size4;
	center6.z = center.z + size4;

	center7.x = center.x - size4;
	center7.y = center.y - size4;
	center7.z = center.z + size4;

	center8.x = center.x + size4;
	center8.y = center.y - size4;
	center8.z = center.z + size4;

	res.push_back(Voxel(center1, size /2));
	res.push_back(Voxel(center2, size /2));
	res.push_back(Voxel(center3, size /2));
	res.push_back(Voxel(center4, size /2));
	res.push_back(Voxel(center5, size /2));
	res.push_back(Voxel(center6, size /2));
	res.push_back(Voxel(center7, size /2));
	res.push_back(Voxel(center8, size /2));
	return res;
}

bool Voxel::intersectSphere(Point center, double rayon) {
	for (int i = 0; i< points.size(); i++) {
		if (center.distance(points[i]) < rayon) {
			return true;
		}
	}
	return false;
}

void Voxel::displaySphereRecurs(Point center, double rayon, int resolution, int currentRes) {
	if (this->intersectSphere(center, rayon)) {
		if (currentRes >= resolution) {
			this->display();
		} else {
			++currentRes;
			vector<Voxel> voxels = this->divide();
			for (int i=0; i<voxels.size(); i++) {
				voxels[i].displaySphereRecurs(center, rayon, resolution, currentRes);
			}
		}
	}
}

void Voxel::displaySphere(Point center, double rayon, int resolution) {
	Voxel v = Voxel(center, rayon*2);
	vector<Voxel> voxels = v.divide();
	for (int i=0; i<voxels.size(); i++) {
		voxels[i].displaySphereRecurs(center, rayon, resolution, 1);
	}
}

bool Voxel::intersectCylinder(Point middle, Vector axis, double rayon) {
	for (int i = 0; i< points.size(); i++) {
		Point proj = points[i].projectOnLine(axis, middle);
		if (middle.distance(proj) < axis.norme() / 2 &&
			proj.distance(points[i]) < rayon) {
			return true;
		}
	}
	return false;
}

void Voxel::displayCylinderRecus(Point middle, Vector axis, double rayon, int resolution, int currentRes) {
	if (this->intersectCylinder(middle, axis, rayon)) {
		if (currentRes >= resolution) {
			this->display();
		} else {
			++currentRes;
			vector<Voxel> voxels = this->divide();
			for (int i=0; i<voxels.size(); i++) {
				voxels[i].displayCylinderRecus(middle, axis, rayon, resolution, currentRes);
			}
		}
	}
}

void Voxel::displayCylinder(Point origin, Vector axis, double rayon, int resolution) {
	Point middle = axis.middle(origin);
	double bigger = rayon > axis.norme() ? rayon : axis.norme();
	Voxel v = Voxel(middle, bigger);
	vector<Voxel> voxels = v.divide();
	for (int i=0; i<voxels.size(); i++) {
		voxels[i].displayCylinderRecus(middle, axis, rayon, resolution, 1);
	}
}

void Voxel::displayIntersectionRec(Sphere s, Cylinder c, int resolution, int currentRes) {
	if (this->intersectCylinder(c.middle, c.axis, c.rayon) &&
		this->intersectSphere(s.center, s.rayon)) {
		if (currentRes >= resolution) {
			this->display();
		} else {
			++currentRes;
			vector<Voxel> voxels = this->divide();
			for (int i=0; i<voxels.size(); i++) {
				voxels[i].displayIntersectionRec(s, c, resolution, currentRes);
			}
		}
	}
}

void Voxel::displayIntersection(Sphere s, Cylinder c, int resolution) {
	Vector vec = Vector::FromPoint(c.middle, s.center);
	Point middle = vec.middle(c.middle);
	double size = vec.norme() + s.rayon * 2 + c.axis.norme() *2;
	Voxel v = Voxel(middle, size);
	vector<Voxel> voxels = v.divide();
	for (int i=0; i<voxels.size(); i++) {
		voxels[i].displayIntersectionRec(s, c, resolution, 1);
	}
}

void Voxel::displayUnionRec(Sphere s, Cylinder c, int resolution, int currentRes) {
	if (this->intersectCylinder(c.middle, c.axis, c.rayon) ||
		this->intersectSphere(s.center, s.rayon)) {
		if (currentRes >= resolution) {
			this->display();
		} else {
			++currentRes;
			vector<Voxel> voxels = this->divide();
			for (int i=0; i<voxels.size(); i++) {
				voxels[i].displayUnionRec(s, c, resolution, currentRes);
			}
		}
	}
}

void Voxel::displayUnion(Sphere s, Cylinder c, int resolution) {
	Vector vec = Vector::FromPoint(c.middle, s.center);
	Point middle = vec.middle(c.middle);
	double size = vec.norme() + s.rayon * 2 + c.axis.norme() *2;
	Voxel v = Voxel(middle, size);
	vector<Voxel> voxels = v.divide();
	for (int i=0; i<voxels.size(); i++) {
		voxels[i].displayUnionRec(s, c, resolution, 1);
	}
}

void Voxel::displaySoustractionRec(Sphere s, Cylinder c, int resolution, int currentRes) {
	if (this->intersectSphere(s.center, s.rayon)) {
		if (currentRes >= resolution) {
			if (!this->intersectCylinder(c.middle, c.axis, c.rayon)) {
				this->display();
			}
		} else {
			++currentRes;
			vector<Voxel> voxels = this->divide();
			for (int i=0; i<voxels.size(); i++) {
				voxels[i].displaySoustractionRec(s, c, resolution, currentRes);
			}
		}
	}
}

void Voxel::displaySoustraction(Sphere s, Cylinder c, int resolution) {
	Vector vec = Vector::FromPoint(c.middle, s.center);
	Point middle = vec.middle(c.middle);
	double size = vec.norme() + s.rayon * 2 + c.axis.norme() *2;
	Voxel v = Voxel(middle, size);
	vector<Voxel> voxels = v.divide();
	for (int i=0; i<voxels.size(); i++) {
		voxels[i].displaySoustractionRec(s, c, resolution, 1);
	}
}


