
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
 
 #include "Trackpoint.h"

 Trackpoint::Trackpoint(Tracktype t, double x, double y, double z, double w, double s) {
 	this->type 	= t;
 	this->x 	= x;
 	this->y 	= y;
 	this->z 	= z;
 	this->weight = w;
    this->size 	= s;
 }

Trackpoint::Trackpoint(Tracktype t, double x, double y, double z, double s) {
 	this->type 	= t;
 	this->x 	= x;
 	this->y 	= y;
 	this->z 	= z;
    this->weight = 0.0f;
    this->size 	= s;
 }
 
 Tracktype Trackpoint::getType() {
	return type;
}

void Trackpoint::setType(Tracktype t) {
	this->type = t;
}
