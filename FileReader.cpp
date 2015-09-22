
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
    
  }
}
