///////////////////////////////////////////////////////////////////////////////
// Imagina
//
// IN - Synth�se d'images - Mod�lisation g�om�trique
// Auteur : Gilles Gesqui�re
//
// Base du TP 1
// programme permettant de cr�er des formes de bases.
// La forme repr�sent�e ici est un polygone blanc dessin� sur un fond
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>

#include <GL/glut.h>

#include "Point.hpp"
#include "Vector.hpp"

#define PI 3.14159265


// D�finition de la taille de la fen�tre
#define WIDTH  480

#define HEIGHT 480

// D�finition de la couleur de la fen�tre
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
#define KEY_Z 122
#define KEY_Q 113
#define KEY_S 115
#define KEY_D 100

#define KEY_A 97
#define KEY_E 101

using namespace std;


vector<Point> control_points;
double precision = 10;
double precision2 = 10;

// Ent�tes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid mouse_event(int button, int state, int x, int y);
GLvoid mouse_motion(int x,int y);
GLvoid special_window_key(int key, int x, int y);

Point camera = Point(1,1,1);


int main(int argc, char **argv) {
	// initialisation  des param�tres de GLUT en fonction
	// des arguments sur la ligne de commande
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);

	// d�finition et cr�ation de la fen�tre graphique, ainsi que son titre
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP");

	// initialisation de OpenGL et de la sc�ne
	initGL();
	init_scene();

	// choix des proc�dures de callback pour
	// le trac� graphique
	glutDisplayFunc(&window_display);
	// le redimensionnement de la fen�tre
	glutReshapeFunc(&window_reshape);
	// la gestion des �v�nements clavier
	glutKeyboardFunc(&window_key);
	glutSpecialFunc(&special_window_key);
	glutMouseFunc(&mouse_event);
	glutMotionFunc(&mouse_motion);

	// la boucle prinicipale de gestion des �v�nements utilisateur
	glutMainLoop();

	return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque
GLvoid initGL()
{
	glClearColor(RED, GREEN, BLUE, ALPHA);
	glPointSize(5.0);
}

void lumiere() {
	glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur
	glEnable(GL_LIGHTING); 	// Active l'éclairage
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// Create light components.
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	// Assign created components to GL_LIGHT0.
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
}

// Initialisation de la scene. Peut servir � stocker des variables devotre programme
// � initialiser
void init_scene()
{
	control_points = vector<Point>();
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// C'est l'endroit o� l'on peut dessiner. On peut aussi faire appel
	// � une fonction (render_scene() ici) qui contient les informations
	// que l'on veut dessiner
	render_scene();

	// trace la sc�ne grapnique qui vient juste d'�tre d�finie
	glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ici, vous verrez pendant le cours sur les projections qu'enmodifiant les valeurs, il est
	// possible de changer la taille de l'objet dans la fen�tre. Augmentezces valeurs si l'objet est
	// de trop grosse taille par rapport � la fen�tre.
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

	// toutes les transformations suivantes s�appliquent au mod�le de vue
	glMatrixMode(GL_MODELVIEW);
}

Point pointFromEvent(int x, int y) {
	double realX = (double) x / (double) glutGet(GLUT_WINDOW_WIDTH);
	double realY = (double) y / (double) glutGet(GLUT_WINDOW_HEIGHT);
	realX = realX * 4 -2 ;
	realY = realY * -4 + 2;
	return Point(realX, realY, 0);
}

bool drag = false;
Point clicPoint = Point(0,0,0);
Vector dragVector;

GLvoid mouse_event(int button, int state, int x, int y) {
	if (button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		drag = true;
		control_points.push_back(pointFromEvent(x,y));
		clicPoint = pointFromEvent(x,y);
	} else if (button ==  GLUT_LEFT_BUTTON && state == GLUT_UP) {
		drag = false;
	}
	glutPostRedisplay();
}

GLvoid mouse_motion(int x,int y) {
	if (drag) {
		dragVector = Vector::FromPoint(clicPoint, pointFromEvent(x,y));
		//camera.x += dragVector.x /10;
		//camera.z += dragVector.y /10;
		glutPostRedisplay();
	}
}

GLvoid special_window_key(int key, int x, int y) {
	switch (key) {

	case GLUT_KEY_UP:
		precision2 ++;
		break;

	case GLUT_KEY_DOWN:
		if (precision2 > 0) precision2 --;
		break;

	case GLUT_KEY_LEFT:
		if (precision > 0) precision --;
		break;

	case GLUT_KEY_RIGHT:
		precision++;
		break;
	}
	glutPostRedisplay();

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {

	case KEY_Z:
		camera.y += 0.1;
		break;

	case KEY_S:
		camera.y -= 0.1;
		break;

	case KEY_Q:
		camera.x -= 0.1;
		break;

	case KEY_D:
		camera.x += 0.1;
		break;

	case KEY_A:
		camera.z -= 0.1;
		break;

	case KEY_E:
		camera.z += 0.1;
		break;

	case KEY_ESC:
		init_scene();
		break;

	default:
		printf ("La touche %d n'est pas active.\n", key);
		break;
	}
	glutPostRedisplay();
}

// UTILS
double fact(int n) {
	double factorial = 1;
	for(int i = 1; i <=n; ++i) {
		factorial *= i;
	}
	return factorial;
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


vector<vector<Point>> surfaceCylindrique(vector<Point> bezier, Vector droite, int precision) {
	vector<vector<Point>> res;
	for (int i = 0; i<=precision; i++) {
		vector<Point> line;
		double u = (double) i / (double) precision;
		for (int j = 0; j < bezier.size(); j++) {
			Point p;
			p.x = bezier[j].x + droite.x * u;
			p.y = bezier[j].y + droite.y * u;
			p.z = bezier[j].z + droite.z * u;
			line.push_back(p);
		}
		res.push_back(line);
	 }
	return res;
}

vector<vector<Point>> surfaceReglee(vector<Point> bezier1, vector<Point> bezier2, int precision) {
	vector<vector<Point>> res;
	for (int i = 0; i <= precision; i++) {
		vector<Point> line;
		double u = (double) i / (double) precision;
		for (int j = 0; j < bezier1.size(); j++) {
			Point p;
			Vector droite = Vector::FromPoint(bezier1[j], bezier2[j]);
			p.x = bezier1[j].x + droite.x * u;
			p.y = bezier1[j].y + droite.y * u;
			p.z = bezier1[j].z + droite.z * u;
			line.push_back(p);
		}
		res.push_back(line);
	 }
	return res;
}

// CURVES
Point* hermiteCubicCurve(Point p0, Point p1, Vector v0, Vector v1, long precision) {
	Point *points = new Point[precision+1];
	for (int i = 0; i <= precision; i++) {
		double u = (double) i / (double) precision;
		double f1 = 2 * pow(u,3) - 3 * pow(u,2) + 1;
		double f2 = - 2 * pow(u,3) + 3 * pow(u,2);
		double f3 = pow(u,3) - 2 * pow(u,2) + u;
		double f4 = pow(u,3) - pow(u,2);
		double x = f1 * p0.x + f2 * p1.x + f3 * v0.x + f4 * v1.x;
		double y = f1 * p0.y + f2 * p1.y + f3 * v0.y + f4 * v1.y;
		double z = f1 * p0.z + f2 * p1.z + f3 * v0.z + f4 * v1.z;
		Point p(x,y,z);
		points[i] = p;
	}
	return points;
}

Point* bezierCurveByCasteljau(Point* controlPoints, long nbControlPoint, long precision) {
	Point *points = new Point[precision+1];
	for (int i = 0; i <= precision; i++) {
		double u =  (double) i / (double) precision;
		Point * temp = new Point[nbControlPoint + 1];
		for (int j = 0; j < nbControlPoint; j++) {
			temp[j] = controlPoints[j];
		}
		for (int j = 1; j < nbControlPoint; j++) {
			for (int k = 0; k < nbControlPoint - j; k++) {
				temp[k] =  temp[k] * (1-u) + temp[k+1] * u;
			}
		}
		points[i] = temp[0];
	}
	return points;
}

Point* bezierCurveByBernstein(Point* controlPoints, long nbControlPoint, long precision) {
	Point *points = new Point[precision+1];
	nbControlPoint--;
	for (int i = 0; i <= precision; i++) {
		double u =  (double) i / (double) precision;
		double x = 0, y = 0, z = 0;
		for (int j = 0; j <= nbControlPoint; j++) {
			double polyBer = fact(nbControlPoint) / (fact(j) * fact(nbControlPoint - j));
			polyBer *= pow(u, j) * pow(1-u, nbControlPoint - j);
			x += polyBer * controlPoints[j].x;
			y += polyBer * controlPoints[j].y;
			z += polyBer * controlPoints[j].z;
		}
		Point p(x,y,z);
		points[i] = p;
	}
	return points;
}

// HELPERS

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

vector<vector<Point>> bezierSurfaceByCasteljau(vector<Point> controlDirectrice, vector<Point> controlGeneratrice, int precision) {
	Point* generatrice = bezierCurveByCasteljau(&controlGeneratrice[0], controlGeneratrice.size(), precision);
	Point* directrice = bezierCurveByCasteljau(&controlDirectrice[0], controlDirectrice.size(), precision);
	vector<vector<Point>> directrices;
	for (int i = 0; i<=precision; i++) {
		vector<Point> line;
		double u = (double) i / (double) precision;
		for (int j = 0; j <= precision; j++) {
			Point p;
			p.x = directrice[j].x + generatrice[i].x * u;
			p.y = directrice[j].y + generatrice[i].y * u;
			p.z = directrice[j].z + generatrice[i].z * u;
			line.push_back(p);
		}
		directrices.push_back(line);
	}
	drawSurface(directrices);

	// Inverse
	vector<vector<Point>> controlLast;
	for (int i=0; i < directrices.size(); i++) {
		vector<Point> line;
		for (int j = 0; j < directrices[i].size(); j++) {
			Point controlPoint = directrices[j][i];
			line.push_back(controlPoint);
		}
		controlLast.push_back(line);
	}

	Point* res[precision+1];
	for (int i=0; i < controlLast.size(); i++) {
		res[i] = bezierCurveByCasteljau(&controlLast[i][0], controlLast[i].size(), precision);
	}

	vector<vector<Point>> resVect;
	for (int i=0; i < controlLast.size(); i++) {
		vector<Point> line;
		for (int j=0; j < controlLast[i].size(); j++) {
			line.push_back(res[i][j]);
		}
		resVect.push_back(line);
	}
	return resVect;
}

void displayCone(int rayon, int hauteur, int nbMeridien) {
	vector<Point> circle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < nbMeridien; i++) {
		double ang = 2 * PI / nbMeridien * i;
		double x = cos(ang) * rayon;
		double y = sin(ang) * rayon;
		circle.push_back(Point(x,y,0));
		glVertex3f(x,y,0);
	}
	glEnd();

	for (int i = 0; i < circle.size(); i++) {
		glBegin(GL_TRIANGLES);
		Point p1 = Point(0,0,hauteur);
		Point p3,p4;
		p3 = circle[i];
		if (i == circle.size() -1) {
			p4 = circle[0];
		} else {
			p4 = circle[i+1];
		}
		glVertex3f(p1.x,p1.y,p1.z);
		glVertex3f(p3.x,p3.y,p3.z);
		glVertex3f(p4.x,p4.y,p4.z);
		glEnd();
	}
}

void displayCylindre(int rayon, int hauteur, int nbMeridien) {
	vector<Point> circle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < nbMeridien; i++) {
		double ang = 2 * PI / nbMeridien * i;
		double x = cos(ang) * rayon;
		double y = sin(ang) * rayon;
		circle.push_back(Point(x,y,0));
		glVertex3f(x,y,0);
	}
	glEnd();

	vector<Point> circle2;

	glBegin(GL_POLYGON);
	for (int i = 0; i < nbMeridien; i++) {
		Point p = circle[i];
		circle2.push_back(Point(p.x, p.y,hauteur));
		glVertex3f(p.x, p.y, hauteur);
	}
	glEnd();

	for (int i = 0; i < circle.size(); i++) {
		glBegin(GL_QUADS);
		Point p1 = circle[i];
		Point p2 = circle2[i];
		Point p3,p4;
		if (i == circle.size() -1) {
			p3 = circle[0];
			p4 = circle2[0];
		} else {
			p3 = circle[i+1];
			p4 = circle2[i+1];
		}
		glVertex3f(p1.x,p1.y,p1.z);
		glVertex3f(p3.x,p3.y,p3.z);
		glVertex3f(p4.x,p4.y,p4.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glEnd();
	}
}

void displaySphere(double rayon, double nbMeridien, double nbParallele)  {
	lumiere();
	vector<vector<Point>> sphere;
	for (int j=0; j<nbMeridien; j++) {
		double theta = 2.0 * PI / nbMeridien * j;
		vector<Point> circle;
		for (int i = 0; i <= nbParallele; i++) {
			double phi = PI / nbParallele * i;
			double x = sin(phi) * rayon * cos(theta);
			double y = sin(phi) * rayon * sin(theta);
			double z = cos(phi) * rayon;
			circle.push_back(Point(x,y,z));
		}
		sphere.push_back(circle);
	}
	sphere.push_back(sphere[0]);

	for (int i=0; i < sphere.size(); i++) {
		for (int j=0; j<sphere[i].size(); j++) {
			glBegin(GL_QUADS);
			int k = (i == sphere.size() -1) ? 0 : i+1;
			int l = (j == sphere[i].size() - 1) ? 0 : j+1;
			Point p1 = sphere[i][j];
			Point p2 = sphere[k][j];
			Point p3 = sphere[i][l];
			Point p4 = sphere[k][l];

			glVertex3f(p4.x,p4.y,p4.z);
			glVertex3f(p2.x,p2.y,p2.z);
			glVertex3f(p1.x,p1.y,p1.z);
			glVertex3f(p3.x,p3.y,p3.z);

			glEnd();
		}
	}
	glColor3f(1.0,0,0);
	drawSurface(sphere);
	drawSurface(inverse(sphere));
}


//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////

void render_curve() {
	long size = 30;
	Point a(0,0,0);
	Point b(2,0,0);
	Vector v1(1,1,0);
	Vector v2(1,-1, 0);
	Point* points = hermiteCubicCurve(a, b, v1, v2, size);
	drawPoint(a);
	drawPoint(b);
	drawCurve(points, size + 1);
	drawPoints(points, size + 1);
}

void render_curve_bezier(bool alg) {
	if (control_points.size() < 2) { return; }
	Point* points;
	// control_points.push_back(Point(0,0,0));
	// control_points.push_back(Point(1,1,0));
	// control_points.push_back(Point(1.5,-1.5,0));
	if (alg) {
		points = bezierCurveByCasteljau(&control_points[0], control_points.size(), precision);
	} else {
		points = bezierCurveByBernstein(&control_points[0], control_points.size(), precision);
	}
	drawCurve(points, precision+1);
	drawPoints(points, precision+1);
	glColor3f(1.0, 0, 0);
	drawPoints(&control_points[0], control_points.size());
	drawCurve(&control_points[0], control_points.size());
}

void render_surface_param() {
	glColor3f(1.0, 1.0, 1.0);
	Point* points;
	control_points.push_back(Point(0,0,0));
	control_points.push_back(Point(1,1,0));
	control_points.push_back(Point(1.5,-1.5,0));
	points = bezierCurveByCasteljau(&control_points[0], control_points.size(), precision);
	vector<Point> pointsVect;
	for (int i=0; i < precision + 1;i++) {
		pointsVect.push_back(points[i]);
	}
	vector<vector<Point>> res = surfaceCylindrique(pointsVect, Vector(0,0,1), 20);
	drawSurface(res);
	glColor3f(1.0, 0, 0);
}


void render_surface_regle() {
	glColor3f(1.0, 1.0, 1.0);
	Point* points1;
	vector<Point> control_points1 = vector<Point>();
	control_points1.push_back(Point(2,0,2));
	control_points1.push_back(Point(-1,2,1));
	control_points1.push_back(Point(1.5,1,0));
	points1 = bezierCurveByCasteljau(&control_points1[0], control_points1.size(), precision);
	vector<Point>  control_points2 = vector<Point>();
	Point* points2;
	control_points2.push_back(Point(0,0,0));
	control_points2.push_back(Point(1,2,-1));
	control_points2.push_back(Point(1.5,1.5,0));
	points2 = bezierCurveByCasteljau(&control_points2[0], control_points2.size(), precision);
	vector<Point> pointsVect;
	vector<Point> pointsVect2;
	for (int i=0; i < precision + 1;i++) {
		pointsVect.push_back(points1[i]);
		pointsVect2.push_back(points2[i]);
	}

	glColor3f(1.0, 1.0, 1.0);
	vector<vector<Point>> res = surfaceReglee(pointsVect, pointsVect2, precision);
	drawSurface(res);
	drawSurface(inverse(res));
	glColor3f(1.0, 0, 0);
	drawCurve(&pointsVect[0], pointsVect.size());
	drawCurve(&pointsVect2[0], pointsVect2.size());
}

void render_surface_bezier() {
	glColor3f(1.0, 1.0, 1.0);
	vector<Point> control_points1 = vector<Point>();
	control_points1.push_back(Point(0,0,0));
	control_points1.push_back(Point(1,0,0));
	control_points1.push_back(Point(2,0,1));
	drawControlPoints(control_points1);

	vector<Point> control_points2 = vector<Point>();
	control_points2.push_back(Point(0,0,0));
	control_points2.push_back(Point(0,1,-1));
	control_points2.push_back(Point(0,2,0));
	drawControlPoints(control_points2);

	vector<vector<Point>> res = bezierSurfaceByCasteljau(control_points1, control_points2, precision);
	drawSurface(res);
}

void tp1() {

	Point a(-1,-1, 0);
	Point b(1,1,0);
	Point p(1.5,1,0);
	Point proj = p.projectOnLine(a, b);
	drawPoint(p);
	drawLine(a, b);
	drawPoint(proj);

	// Vector v(-1.5,-5,0);
	// drawLine(proj, v);
	// Point proj2 = a.projectOnLine(v,proj);
	// drawPoint(proj2);

	//  Nous cr�ons ici un polygone. Nous pourrions aussi cr�er untriangle ou des lignes. Voir ci-dessous les parties
	// en commentaires (il faut commenter le bloc qui ne vous int�ressepas et d�commenter celui que vous voulez tester.

	// cr�ation d'un polygone
		// glBegin(GL_POLYGON);
		// 	glVertex3f(-1, -1, 0);
		// 	glVertex3f(1, -1, 0);
		// 	glVertex3f(1, 1, 0);
		// 	glVertex3f(-1, 1, 0);
		// glEnd();



	/*
	// cr�ation d'un triangle
		glBegin(GL_TRIANGLES);
			glVertex3f(-1, -1, 0);
			glVertex3f(1, -1, 0);
			glVertex3f(1, 1, 0);
		glEnd();
	*/
}

void render_scene()
{
	// Reset transformations
	glLoadIdentity();
	gluPerspective(90.0f,(GLfloat)glutGet(GLUT_WINDOW_WIDTH)/(GLfloat)glutGet(GLUT_WINDOW_HEIGHT), 0.5f, 3000.0f);

	// Set the camera
	gluLookAt(camera.x,camera.y,camera.z, 0,0,0, 0,1,0);
	//D�finition de la couleur
	glColor3f(1.0, 1.0, 1.0);

	Point origin = Point(0,0,0);
	Vector x = Vector(1,0,0);
	Vector y = Vector(0,1,0);
	Vector z = Vector(0,0,1);
	glColor3f(1.0, 0.0, 0.0);
	drawLine(origin, x); // red
	glColor3f(0.0, 1.0, 0.0);
	drawLine(origin, y); // green
	glColor3f(0.0, 0.0, 1.0);
	drawLine(origin, z); // blue

	// drawLine(clicPoint, dragVector);
	// render_curve_bezier(true);
	// render_surface_param();
	// render_surface_regle();
	// render_surface_bezier();
	// displayCylindre(1, 20, 10);
	displayCone(1, 20, 10);
	// displaySphere(1,precision,precision2);
	return;
}

