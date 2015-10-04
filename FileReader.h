
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

#include "Rollercoaster.h"
#include "Trackpoint.h"
#include <string>
#include <iostream>
#include <fstream>

class FileReader {
private:

	float highestPoint;
  	std::ifstream input;

public:

	FileReader();
	FileReader(std::string);

	float getHighest();

  	BSpline readBSpline();
  	Rollercoaster readCoaster();

};

#endif
