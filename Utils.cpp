#include "Utils.hpp"
#include <GL/glut.h>
#include <vector>
#include <cmath>

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

void render_maillage(OffFile off) {
	glColor3f(1.0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, off.points);

	glDrawElements(GL_TRIANGLES, off.nbTriangles*3, GL_UNSIGNED_INT, off.triangles);
	glDisableClientState(GL_VERTEX_ARRAY);
	GLenum err;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		cout << "ERROR: " << err<< endl;
	}
}

OffFile* getOffSphere(double rayon, double nbMeridien, double nbParallele)  {
	vector<Point> sphere;
	vector<TriangleCoord> triangles;

	for (int j=0; j<nbMeridien; j++) {
		double theta = 2.0 * PI / nbMeridien * j;
		for (int i = 0; i <= nbParallele; i++) {
			double phi = PI / nbParallele * i;
			double x = sin(phi) * rayon * cos(theta);
			double y = sin(phi) * rayon * sin(theta);
			double z = cos(phi) * rayon;
			sphere.push_back(Point(x,y,z));
		}
	}

	for (int i=0; i < nbMeridien; i++) {
		for (int j=0; j<=nbParallele; j++) {
			int k = (i == nbMeridien -1) ? 0 : i+1;
			int l = (j == nbParallele) ? 0 : j+1;
			int p1 = i+j;
			int p2 = k+j;
			int p3 = i+l;
			int p4 = k+l;
			triangles.push_back(TriangleCoord(p3,p2,p1));
			triangles.push_back(TriangleCoord(p4,p2,p3));
		}
	}
	return new OffFile(sphere, triangles);
}

OffFile* getOffCylinder(int rayon, int hauteur, int nbMeridien) {
	vector<Point> points;
	vector<TriangleCoord> triangles;
	for (int i = 0; i < nbMeridien; i++) {
		float ang = 2 * PI / nbMeridien * i;
		float x = cos(ang) * rayon;
		float y = sin(ang) * rayon;
		points.push_back(Point(x,y,0));
	}
	for (int i = 0; i < nbMeridien; i++) {
		Point p = points[i];
		points.push_back(Point(p.x, p.y,hauteur));
	}
	points.push_back(Point(0,0,0));
	points.push_back(Point(0,0,hauteur));
	for (int i = 0; i < nbMeridien; i++) {
		int p1 = i;
	 	int p2 = i + 1 == nbMeridien ? 0 : i + 1;
		int p3 = nbMeridien * 2;
		triangles.push_back(TriangleCoord(p1,p2,p3));
		triangles.push_back(TriangleCoord(p1+nbMeridien,p2+nbMeridien,p3+1));
	}

	for (int i = 0; i < nbMeridien; i++) {
		int p1 = i;
		int p2 = i + 1 == nbMeridien ? 0 : i + 1;
		int p3 = nbMeridien + i;
		int p4 = i + 1 == nbMeridien ? nbMeridien : nbMeridien + i + 1;
		triangles.push_back(TriangleCoord(p3,p2,p1));
		triangles.push_back(TriangleCoord(p4,p2,p3));
	}
	return new OffFile(points, triangles);
}


