
#include "BSpline.h"

#define _GLFW_USE_OPENGL

#ifdef __APPLE__
#include "glfw3.h"
#else
#define GLFW_INCLUDE
#include <GLFW/glfw3.h>
#endif

BSpline::BSpline() {
	order = 2;
	knots = KnotSequence(0, order);
}

BSpline::BSpline(int o) {
	order = o;
	knots = KnotSequence(0, order);
}

void BSpline::setOrder(int o) {
	order = o;
}

void BSpline::setX(int pos, double x) {
	controlPoints.at(pos).setX(x);
}

void BSpline::setY(int pos, double y) {
	controlPoints.at(pos).setY(y);
}

void BSpline::setZ(int pos, double z) {
    controlPoints.at(pos).setZ(z);
}

void BSpline::addPoint(controlPoint point) {
	controlPoints.push_back(point);
	knots = KnotSequence((int)controlPoints.size(), order);
}

void BSpline::removePoint(int index) {
	controlPoints.erase(controlPoints.begin() + index);
	knots = KnotSequence((int)controlPoints.size(), order);
}

void BSpline::updateKnots() {
	knots = KnotSequence((int)controlPoints.size(), order);
}

void BSpline::clearPoints() {
	controlPoints.clear();
	knots = KnotSequence(0, order);
}

std::vector<controlPoint> BSpline::getPoints() {
	return controlPoints;
}

Vertex BSpline::getPoint(double u, bool drawGeo) {
  double w = 0;
	int k = order;
	int delta;
	std::vector<controlPoint> p = controlPoints;
	std::vector<Vertex> c = std::vector<Vertex>();
	std::vector<controlPoint> e;
	
    delta = knots.getDelta(u);
    for(int i = 0; i <= k - 1; i++) {
        if(delta - i > p.size() - 1) {
            c.push_back(p.at(p.size() - 1));
        }
        else {
            c.push_back(p.at(delta - i));
        }
        
    }

    for(int r = k; r >= 2; r--) {
        int i = delta;
        for(int s = 0; s < r - 1; s++) {
            w = (u - knots.getValue(i))/(knots.getValue(i + r - 1) - knots.getValue(i));
            if(drawGeo) {
                glBegin(GL_LINES);
                glVertex3f(c.at(s).getX(), c.at(s).getY(), c.at(s).getZ());
                glVertex3f(c.at(s+1).getX(), c.at(s+1).getY(), c.at(s+1).getZ());
                glEnd();
            }
            c[s] = (c.at(s) * w) + (c.at(s+1) * (1 - w));
            i--;
        }
    }
	return c.at(0);
}
