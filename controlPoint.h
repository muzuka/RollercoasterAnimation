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

class Controlpoint : public Vertex {
	
private:
  double 		size;
	double 		weight;

public:
	Controlpoint();
	Controlpoint(double, double, double, double, double);
	Controlpoint(double, double, double, double);

  bool isClicked(double, double);
};

#endif
