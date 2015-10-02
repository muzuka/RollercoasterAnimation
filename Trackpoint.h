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

#include "controlPoint.h"

enum Tracktype {CHAIN, FREE, END};

class Trackpoint : public controlPoint {
private:
  Tracktype	type;
  
public:
	controlPoint(Tracktype, double, double, double, double, double);
	controlPoint(Tracktype, double, double, double, double);
  
  Tracktype getType();
	void setType(Tracktype);
}

#endif
