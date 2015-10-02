#ifndef _BSPLINE_H_
#define _BSPLINE_H_

/*
 * B Spline class
 *
 * contains a collection of control points
 * 
 * From CPSC 589
 *
 * Sean Brown
 *
 */

 #include <vector>
 #include "KnotSequence.h"
 #include "Controlpoint.h"
 #include "Vertex.h"

class BSpline {

protected:

	int order;
	KnotSequence knots;
	std::vector<Controlpoint> controlpoints;

public:

	BSpline();
	BSpline(int);

	void setOrder(int);
	int  getOrder();

	void setX(int, double);
	void setY(int, double);
	void setZ(int, double);
	void addPoint(Controlpoint);
	void removePoint(int);

	void updateKnots();
	void clearPoints();

	std::vector<Controlpoint> getPoints();

	Vertex getPoint(double);

};

#endif
