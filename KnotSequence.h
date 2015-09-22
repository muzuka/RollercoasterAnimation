#ifndef _KNOTSEQUENCE_H_
#define _KNOTSEQUENCE_H_

/*
 * CPSC 589
 *
 * knot sequence class
 *  - represents the knot sequence and manipulates it
 *  - can be queried with getValue
 *
 *
 * Sean Brown
 *
 */

#include <vector>

class KnotSequence {
private:
	double inc;
	int order;
	std::vector<double> knots;

public:
	KnotSequence();
	KnotSequence(int, int);

	void setOrder(int);
	void setInc(double);

	int getOrder();
	double getInc();
    int getKnotCount();

	void createSequence();

	double getValue(double); // get value of knot
	double getValue(int);
    
    int getDelta(double);

};

#endif