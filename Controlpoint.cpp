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

 #include "Controlpoint.h"

Controlpoint::Controlpoint() {
	
}

 Controlpoint::Controlpoint(double x, double y, double z, double w, double s) {
 	this->x 		= x;
 	this->y 		= y;
 	this->z 		= z;
 	this->weight 	= w;
    this->size 		= s;
 }

 Controlpoint::Controlpoint(double x, double y, double z, double s) {
 	this->x 		= x;
 	this->y 		= y;
 	this->z 		= z;
    this->weight 	= 0.0f;
    this->size 		= s;
 }

Controlpoint Controlpoint::operator*(double arg) {
    return Controlpoint(x*arg, y*arg, z*arg, weight, 1.0f);
}

Controlpoint Controlpoint::operator+(Controlpoint arg) {
    return Controlpoint(x + arg.getX(), y + arg.getY(), z + arg.getZ(), weight, 1.0f);
}

Controlpoint Controlpoint::operator-(Controlpoint arg) {
    return Controlpoint(x - arg.getX(), y - arg.getY(), z - arg.getZ(), weight, 1.0f);
}
 
 double Controlpoint::getSize() {
   return size;
 }
 
 double Controlpoint::getWeight() {
   return weight;
 }

bool Controlpoint::isClicked(double x, double y) {
    
    double dis = size/2.0f;
    
    if ((x >= this->x - dis && x <= this->x + dis) && (y >= this->y - dis && y <= this->y + dis)) {
        return true;
    }
    
    return false;
}
