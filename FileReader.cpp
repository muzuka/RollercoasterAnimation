
#include "FileReader.h"
#include <iostream>

FileReader::FileReader() {
  input = std::ifstream();
}

FileReader::FileReader(std::string file) {
  input = std::ifstream(file.c_str());
}

BSpline FileReader::readBSpline() {
  if(!input.is_open()) {
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
