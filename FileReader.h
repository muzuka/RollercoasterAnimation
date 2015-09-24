
/*
 * FileReader class
 *
 * reads control points from a file
 *
 * Sean Brown
 *
 */

#ifndef FILEREADER_H
#define FILEREADER_H

#include "BSpline.h"
#include <string>
#include <iostream>
#include <fstream>

class FileReader {
private:

  std::ifstream input;

public:

	FileReader();
	FileReader(std::string);

  BSpline readBSpline();

};

#endif
