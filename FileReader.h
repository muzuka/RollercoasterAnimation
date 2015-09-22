
#ifndef FILEREADER_H
#define FILEREADER_H

#include "BSpline.h"
#include <string>
#include <iostream>
#include <ifstream>

class FileReader {
private:

  ifstream input;

public:

	FileReader();
	FileReader(string);

  BSpline readBSpline();

}

#endif
