
/*
 * Frenetframe class
 *  - represents frenet frame.
 *
 *
 * Sean Brown
 *
 */

#ifndef FRENETFRAME_H
#define FRENETFRAME_H

#include "Rollercoaster.h"

class Frenetframe {
private:

  Vertex t; // tangent
  Vertex n; // normal
  Vertex b; // binormal

public:

  Frenetframe();
  Frenetframe(Vertex, Vertex, Vertex);
  
  Vertex getTangent();
  Vertex getNormal();
  Vertex getBinormal();
  
  void setTangent(Vertex);
  void setNormal(Vertex);
  void setBinormal(Vertex);
  
  static Frenetframe computeFrenet(Vertex, Vertex, Vertex);
};

#endif
