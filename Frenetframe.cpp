
/*
 * Frenetframe class implementation
 *  - represents frenet frame.
 *
 *
 * Sean Brown
 *
 */

#include "Frenetframe.h"

Frenetframe::Frenetframe() {
  this->t = Vertex();
  this->n = Vertex();
  this->b = Vertex();
}

Frenetframe::Frenetframe(Vertex t, Vertex n, Vertex b) {
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

Frenetframe Frenetframe::computeFrenet(Vertex first, Vertex second, Vertex third) {
  //double h = ((third - (second * 2) + first) / 2).length();
  //double c = (third - first).length();
  //double r = (c * c) + (4 * (h * h)) / (8 * h);
  
  Frenetframe frame = Frenetframe();
  Vertex tangent = (third - second);
  tangent.normalize();
  bool straight = (second - first) == (third - second);
  
  frame.setTangent(tangent);
  if(straight) {
    frame.setNormal(Vertex(0.0f, 1.0f, 0.0f));
    frame.setBinormal(Vertex::crossProduct(tangent, frame.getNormal()));
  }
  else {
    Vertex midPoint = ((third - first) / 2.0f) + first;
    Vertex force = (midPoint - second);
    force.normalize();
    
    frame.setNormal(force);
    frame.setBinormal(Vertex::crossProduct(frame.getNormal(), tangent));
  }
  
  return frame;
}
