
#include "Frenetframe.h"

Frenetframe::Frenetframe() {
  this->t = Vertex();
  this->n = Vertex();
  this->b = Vertex();
}

Frenetframe::Frenetframe(Vertex t, Vertex n, Vertex, b) {
  this->t = t;
  this->n = n;
  this->b = b;
}

Vertex Frenetframe::getTangent() {
  return t;
}

Vertex Frenetframe::getNormal() {
  return n;
}

Vertex Frenetframe::getBinormal() {
  return b;
}

void Frenetframe::setTangent(Vertex t) {
  this->t = t;
}

void Frenetframe::setNormal(Vertex n) {
  this->n = n;
}

void Frenetframe::setBinormal(Vertex b) {
  this->b = b;
}

Fernetframe Frenetframe::computeFrenet(Rollercoaster coaster, double u, Vertex first, Vertex second, Vertex, last) {
  double h = ((last - (second * 2) + first) / 2).length();
  double c = (last - first).length();
  double r = (c * c) + (4 * (h * h)) / (8 * h);

  Rollercoaster dCoaster = coaster.getDerivative();
  
  this->t = dCoaster.getPoint(u);
  
  this->n; 

  this->b;
}
