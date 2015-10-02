
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
 
 Trackpoint::Trackpoint() {
   this->type = FREE;
   Controlpoint();
 }
 
 Trackpoint::Trackpoint(Tracktype t) {
   this->type = t;
   Controlpoint();
 }

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
 
 void Trackpoint::operator=(Vertex v) {
   this->x = v.getX();
   this->y = v.getY();
   this->z = v.getZ();
   this->type = FREE;
 }
 
 void Trackpoint::operator=(Controlpoint p) {
   this->x = p.getX();
   this->y = p.getY();
   this->z = p.getZ();
   this->weight = p.getWeight();
   this->size = p.getSize();
   this->type = FREE;
 }
 
 Tracktype Trackpoint::getType() {
	return type;
}

void Trackpoint::setType(Tracktype t) {
	this->type = t;
}
