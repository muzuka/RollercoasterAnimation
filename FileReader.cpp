
#include "FileReader.h"
#include <iostream>

FileReader::FileReader() {
  input = ifstream();
}

FileReader::FileReader(string file) {
  input = ifstream(file.c_str());
}

BSpline FileReader::readBSpline() {
  if(!input.open()) {
    printf("Fatal file error\n");
    exit(EXIT_FAILURE);
  }
  
  BSpline newSpline(3);
  int numOfControlPoints;
  double x, y, z, w;
  
  input >> numOfControlPoints;
  
  for(int i = 0; i < numOfControlPoints; i++) {
    input >> x;
    input >> y;
    input >> z;
    input >> w;
    
    newSpline.addPoint(controlPoint(x, y, z, w, 1.0f));
  }
  
  return newSpline;
}
