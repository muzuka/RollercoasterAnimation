
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
 
 Trackpoint::Trackpoint(Tracktype t, Vertex v) {
  this->type = t;
  this->x 	= v.getX();
 	this->y 	= v.getY();
 	this->z 	= v.getZ();
 }
 
 Trackpoint::Trackpoint(Tracktype t, Controlpoint c) {
  this->type = t;
  this->x 	= c.getX();
 	this->y 	= c.getY();
 	this->z 	= c.getZ();
  this->weight = c.getWeight();
  this->size 	= c.getSize();
 }

Trackpoint Trackpoint::operator*(double arg) {
  return Trackpoint(type, x*arg, y*arg, z*arg, weight, 1.0f);
}

Trackpoint Trackpoint::operator+(Trackpoint arg) {
  return Trackpoint(type, x + arg.getX(), y + arg.getY(), z + arg.getZ(), weight, 1.0f);
}

Trackpoint Trackpoint::operator-(Trackpoint arg) {
  return Trackpoint(type, x - arg.getX(), y - arg.getY(), z - arg.getZ(), weight, 1.0f);
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

void Trackpoint::printType() {
  switch(type) {
    case CHAIN:
      printf("CHAIN\n");
      break;
    case FREE:
      printf("FREE\n");
      break;
    case END:
      printf("END\n");
      break;
  }
}
