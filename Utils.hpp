#pragma once
#include "Point.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glut.h>

const double PI = 3.14159265;

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

struct TriangleCoord {
	GLuint a, b, c;
	TriangleCoord(){}
	TriangleCoord(GLuint a, GLuint b, GLuint c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
};

struct OffFile {
	int nbSommets = -1;
	int nbTriangles = -1;
	GLfloat* points;
	GLuint* triangles;

	OffFile(vector<Point> pts, vector<TriangleCoord> trgls) {
		nbSommets = pts.size();
		points = new GLfloat[nbSommets*3];
		for (int i = 0; i<nbSommets; i++) {
			points[i*3] = pts[i].x;
			points[i*3+1] = pts[i].y;
			points[i*3+2] = pts[i].z;
		}
		nbTriangles = trgls.size();
		triangles = new GLuint[nbTriangles*3];
		for (int i = 0; i < nbTriangles; i++) {
			triangles[i*3] = trgls[i].a;
			triangles[i*3+1] = trgls[i].b;
			triangles[i*3+2] = trgls[i].c;
		}
	};

	OffFile(char * filename) {
		string line;
		ifstream file (filename);
		if (file.is_open()) {
			int lineNumber = 0;
			while (getline(file,line)) {
				lineNumber ++;
				istringstream iss(line);
				if (lineNumber == 1) {
				} else if (lineNumber == 2) {
					iss >> nbSommets >> nbTriangles;
					points = new GLfloat[nbSommets*3];
					triangles = new GLuint[nbTriangles*3];
				} else if (nbSommets != -1 && lineNumber - 3 < nbSommets) {
					int tabOffset = (lineNumber - 3);
					GLfloat x,y,z;
					iss >> x >> y >> z;
					points[tabOffset * 3] = x;
					points[tabOffset * 3 + 1] = y;
					points[tabOffset * 3 + 2] = z;
				} else if (nbTriangles != -1 && lineNumber - 3 - nbSommets < nbTriangles) {
					int tabOffset = (lineNumber - 3) - nbSommets;
					GLuint a,b,c,unused;
					iss >> unused >> a >> b >> c;
					triangles[tabOffset * 3] = a;
					triangles[tabOffset * 3 + 1] = b;
					triangles[tabOffset * 3 + 2] = c;
				}
			}
			file.close();
			// cout << "nb : " << nbSommets << " | " << nbTriangles << endl;
			// cout << triangles[2] << " | " << triangles[nbTriangles*3-2] << endl;
		} else {
			cout << "Unable to open file";
		}
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
OffFile* getOffCylinder(int rayon, int hauteur, int nbMeridien);
OffFile* getOffSphere(double rayon, double nbMeridien, double nbParallele);
void render_maillage(OffFile off);
