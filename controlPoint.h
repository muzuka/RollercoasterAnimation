 #ifndef _CONTROLPOINT_H_
 #define _CONTROLPOINT_H_

/*
 * CPSC 589
 *
 * Control Point class
 *
 * Sean Brown
 *
 */

 #include "Vertex.h"

class controlPoint : public Vertex {
	
private:
    double size;
	double weight;

public:
	controlPoint();
	controlPoint(double, double, double, double, double);
	controlPoint(double, double, double, double);

    bool isClicked(double, double);
};

#endif