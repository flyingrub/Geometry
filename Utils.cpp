#include "Utils.hpp"
#include <GL/glut.h>
#include <vector>

using namespace std;

double fact(int n) {
	double factorial = 1;
	for(int i = 1; i <=n; ++i) {
		factorial *= i;
	}
	return factorial;
}

void drawPoint(Point p) {
	glBegin(GL_POINTS);
		glVertex3f(p.x, p.y, p.z);
	glEnd();
}

void drawPoints(Point *points, long nbPoints) {
	for (int i=0; i < nbPoints; i++) {
		drawPoint(points[i]);
	}
}

void drawLine(Point a, Point b) {
	glBegin(GL_LINES);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
	glEnd();
}

void drawLine(Point a, Vector v) {
	Point b;
	b.x = a.x + v.x;
	b.y = a.y + v.y;
	b.z = a.z + v.z;
	glBegin(GL_LINES);
		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
	glEnd();
}

void drawCurve(Point *points, long nbPoints) {
	glBegin(GL_LINE_STRIP);
	for (int i=0; i < nbPoints; i++) {
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();
}

void drawControlPoints(vector<Point> points) {
	glColor3f(1.0, 0, 0);
	drawCurve(&points[0], points.size());
	drawPoints(&points[0], points.size());
}

void drawSurface(vector<vector<Point>> surface) {
	for (int i=0; i < surface.size(); i++) {
		drawCurve(&surface[i][0], surface[i].size());
	}
}

vector<vector<Point>> inverse(vector<vector<Point>> surface) {
	vector<vector<Point>> controlLast;
	for (int i=0; i < surface[0].size(); i++) {
		vector<Point> line;
		for (int j = 0; j < surface.size(); j++) {
			Point controlPoint = surface[j][i];
			line.push_back(controlPoint);
		}
		controlLast.push_back(line);
	}
	return controlLast;
}

double randZeroToOne() {
    return rand() / (RAND_MAX + 1.);
}

void randomColor() {
    glColor3f(randZeroToOne(), randZeroToOne(), randZeroToOne());
}


