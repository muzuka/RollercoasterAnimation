
/*
 * FileReader class
 *
 * reads control points from a file
 *
 * Sean Brown
 *
 */

#include "FileReader.h"
#include <iostream>

FileReader::FileReader() {
  highestPoint = 0.0f;
  input = std::ifstream();
}

FileReader::FileReader(std::string file) {
  highestPoint = 0.0f;
  input = std::ifstream(file.c_str());
}

float FileReader::getHighest() {
  return highestPoint;
}

BSpline FileReader::readBSpline() {
  if(!input.is_open()) {
    printf("Fatal file error\n");
    exit(EXIT_FAILURE);
  }
  
  BSpline newSpline(3);
  Controlpoint firstPoint;
  int numOfControlpoints;
  double x, y, z, w;
  
  input >> numOfControlpoints;
  
  for(int i = 0; i < numOfControlpoints; i++) {
    input >> x;
    input >> y;
    input >> z;
    input >> w;

    if(i == numOfControlpoints - 1) {
      firstPoint = Controlpoint(x, y, z, w, 1.0f);
    }

    if(y > highestPoint)
      highestPoint = y;
    
    newSpline.addPoint(Controlpoint(x, y, z, w, 1.0f));
  }
  
  newSpline.insertPoint(0, firstPoint);
  
  return newSpline;
}

Rollercoaster FileReader::readCoaster() {
  if(!input.is_open()) {
    printf("Fatal file error\n");
    exit(EXIT_FAILURE);
  }
  
  Rollercoaster newCoaster(3);
  Controlpoint firstPoint;
  Trackpoint firstTrack;
  Tracktype currentType;
  int numOfControlpoints;
  char type;
  double x, y, z, w;
  
  input >> numOfControlpoints;
  
  for(int i = 0; i < numOfControlpoints; i++) {
    input >> type;
    input >> x;
    input >> y;
    input >> z;
    input >> w;

    if(y > highestPoint)
      highestPoint = y;
    
    if(type == 'c') {
      currentType = CHAIN;
    }
    else if(type == 'f') {
      currentType = FREE;
    }
    else if(type == 'e') {
      currentType = END;
    }

    if(i == numOfControlpoints - 1) {
      firstPoint = Controlpoint(x, y, z, w, 1.0f);
      firstTrack = Trackpoint(currentType, x, y, z, w, 1.0f);
    }

    newCoaster.addTrack(Trackpoint(currentType, x, y, z, w, 1.0f));
    newCoaster.addPoint(Controlpoint(x, y, z, w, 1.0f));
  }

  newCoaster.insertPoint(0, firstPoint);
  newCoaster.insertTrack(0, firstTrack);
  
  return newCoaster;
}
