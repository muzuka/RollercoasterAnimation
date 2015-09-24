/*
 * vertex class
 *  - represents vertex that forms the curve.
 *
 * From CPSC 589
 *
 * Sean Brown
 *
 */


 #include "Vertex.h"

Vertex::Vertex() {

}

 Vertex::Vertex(double x, double y, double z) {
 	this->x = x;
 	this->y = y;
 	this->z = z;
 }

 Vertex Vertex::operator*(double arg) {
 	return Vertex(this->x*arg, this->y*arg, this->z*arg);
 }

 Vertex Vertex::operator+(Vertex v) {
 	return Vertex(v.x + this->x, v.y + this->y, v.z + this->z);
 }

double Vertex::getX() {
	return this->x;
}

double Vertex::getY() {
	return this->y;
}

double Vertex::getZ() {
	return this->z;
}

void Vertex::setX(double x) {
	this->x = x;
}

void Vertex::setY(double y) {
	this->y = y;
}

void Vertex::setZ(double z) {
	this->z = z;
}
