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
 #include "controlPoint.h"
 #include "Vertex.h"

class BSpline {

private:

	int order;
	KnotSequence knots;
	std::vector<controlPoint> controlPoints;

public:

	BSpline();
	BSpline(int);

	void setOrder(int);
	int  getOrder();

	void setX(int, double);
	void setY(int, double);
	void setZ(int, double);
	void addPoint(controlPoint);
	void removePoint(int);

	void updateKnots();
	void clearPoints();

	std::vector<controlPoint> getPoints();

	Vertex getPoint(double);

};

#endif
