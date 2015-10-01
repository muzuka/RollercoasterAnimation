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

 #include "controlPoint.h"

controlPoint::controlPoint() {
	
}

 controlPoint::controlPoint(double x, double y, double z, double w, double s) {
 	this->x 		= x;
 	this->y 		= y;
 	this->z 		= z;
 	this->weight 	= w;
    this->size 		= s;
 }

 controlPoint::controlPoint(double x, double y, double z, double s) {
 	this->x 		= x;
 	this->y 		= y;
 	this->z 		= z;
    this->weight 	= 0.0f;
    this->size 		= s;
 }

 controlPoint::controlPoint(Tracktype t, double x, double y, double z, double w, double s) {
 	this->type 	= t;
 	this->x 	= x;
 	this->y 	= y;
 	this->z 	= z;
 	this->weight = w;
    this->size 	= s;
 }

controlPoint::controlPoint(Tracktype t, double x, double y, double z, double s) {
 	this->type 	= t;
 	this->x 	= x;
 	this->y 	= y;
 	this->z 	= z;
    this->weight = 0.0f;
    this->size 	= s;
 }

Tracktype controlPoint::getType() {
	return type;
}

void controlPoint::setType(Tracktype t) {
	this->type = t;
}

bool controlPoint::isClicked(double x, double y) {
    
    double dis = size/2.0f;
    
    if ((x >= this->x - dis && x <= this->x + dis) && (y >= this->y - dis && y <= this->y + dis)) {
        return true;
    }
    
    return false;
}
