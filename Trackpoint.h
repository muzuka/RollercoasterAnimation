#ifndef TRACKPOINT_H
#define TRACKPOINT_H

/*
 * CPSC 589
 *
 * Track Point class
 * 
 * From CPSC 589
 *
 * Sean Brown
 *
 */

#include "Controlpoint.h"

enum Tracktype {CHAIN, FREE, END};

class Trackpoint : public Controlpoint {
private:
  Tracktype	type;
  
public:
	Trackpoint();
	Trackpoint(Tracktype);
	Trackpoint(Tracktype, double, double, double, double, double);
	Trackpoint(Tracktype, double, double, double, double);
  
	Trackpoint operator*(double);
	Trackpoint operator+(Trackpoint);
	Trackpoint operator-(Trackpoint);

	void operator=(Vertex);
	void operator=(Controlpoint);
  
	Tracktype getType();
	void setType(Tracktype);
	void printType();

};

#endif
