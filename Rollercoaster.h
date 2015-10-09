#ifndef ROLLERCOASTER_H
#define ROLLERCOASTER_H

/*
 * CPSC 589
 *
 * Rollercoaster class
 * 
 * From CPSC 589
 *
 * Sean Brown
 *
 */
 
#include "BSpline.h"
#include "Trackpoint.h"

class Rollercoaster : public BSpline {
private:
  std::vector<Trackpoint> tracks;
  
public:

  Rollercoaster();
  Rollercoaster(int);
  
  void setX(int, double);
	void setY(int, double);
	void setZ(int, double);
  
  void insertTrack(int, Trackpoint);
  void addTrack(Trackpoint);
  void removeTrack(int);
  
  std::vector<Trackpoint> getTracks();
  void clearPoints();
  
  Trackpoint getTrack(double);

  Rollercoaster getDerivative();
};

#endif
