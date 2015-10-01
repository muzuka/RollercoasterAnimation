 #ifndef _CONTROLPOINT_H_
 #define _CONTROLPOINT_H_

/*
 * CPSC 589
 *
 * Control Point class
 * 
 * From CPSC 589
 *
 * Sean Brown
 *
 */

 #include "Vertex.h"

enum Tracktype {CHAIN, FREE, END};

class controlPoint : public Vertex {
	
private:
	Tracktype	type;
    double 		size;
	double 		weight;

public:
	controlPoint();
	controlPoint(double, double, double, double, double);
	controlPoint(double, double, double, double);
	controlPoint(Tracktype, double, double, double, double, double);
	controlPoint(Tracktype, double, double, double, double);

	Tracktype getType();
	void setType(Tracktype);

    bool isClicked(double, double);
};

#endif
