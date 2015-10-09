
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
 
 #include "Rollercoaster.h"
 
 Rollercoaster::Rollercoaster() {
  order = 2;
  knots = KnotSequence(0, order);
 }
 
 Rollercoaster::Rollercoaster(int o) {
  order = o;
  knots = KnotSequence(0, order);
 }
 
  void Rollercoaster::setX(int pos, double x) {
    controlpoints[pos].setX(x);
    tracks[pos].setX(x);
  }
  
	void Rollercoaster::setY(int pos, double y) {
    controlpoints[pos].setY(y);
    tracks[pos].setY(y);
  }
  
	void Rollercoaster::setZ(int pos, double z) {
    controlpoints[pos].setZ(z);
    tracks[pos].setZ(z);
  }

  void Rollercoaster::insertTrack(int p, Trackpoint tp) {
    tracks.insert(tracks.begin() + p, tp);
  }
  
  void Rollercoaster::addTrack(Trackpoint n) {
    tracks.push_back(n);
  }
  
  void Rollercoaster::removeTrack(int index) {
    tracks.erase(tracks.begin() + index);
  }

  std::vector<Trackpoint> Rollercoaster::getTracks() {
    return tracks;
  }
  
  void Rollercoaster::clearPoints() {
    controlpoints.clear();
    tracks.clear();
  }
  
  Trackpoint Rollercoaster::getTrack(double u) {
    double w = 0;
    unsigned int k = order;
    unsigned int delta;
    std::vector<Trackpoint> p = tracks;
    std::vector<Trackpoint> c = std::vector<Trackpoint>();
    std::vector<Controlpoint> e;
    
      delta = knots.getDelta(u);
      for(unsigned int i = 0; i <= k - 1; i++) {
          Trackpoint newPoint;
          if(delta - i > p.size() - 1) {
              newPoint = p.at(p.size() -1);
              c.push_back(newPoint);
          }
          else {
              newPoint = p.at(delta - i);
              c.push_back(newPoint);
          }
          
      }

      for(int r = k; r >= 2; r--) {
          int i = delta;
          for(int s = 0; s < r - 1; s++) {
              w = (u - knots.getValue(i))/(knots.getValue(i + r - 1) - knots.getValue(i));
              c[s] = (c.at(s) * w) + (c.at(s+1) * (1 - w));
              i--;
          }
      }
    return c.at(0);
  }

  Rollercoaster Rollercoaster::getDerivative() {
    Rollercoaster newCoaster = Rollercoaster(order - 1);

    for(int i = 0; i < controlpoints.size() - 1; i++) {
      newCoaster.addTrack((tracks[i+1] - tracks[i]) * (order/(knots.getValue(i+order+1) - knots.getValue(i+1))));
      newCoaster.addPoint((controlpoints[i+1] - controlpoints[i]) * (order/(knots.getValue(i+order+1) - knots.getValue(i+1))));
    }

    return newCoaster;
  }
