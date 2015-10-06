
/*
 * knot sequence class
 *  - represents the knot sequence and manipulates it
 *  - can be queried with getValue
 *
 * From CPSC 589
 *
 * Sean Brown
 *
 */

#include "KnotSequence.h"
#include <stdio.h>
#include <math.h>

KnotSequence::KnotSequence() {
	inc = 0;
	order = 0;
}

KnotSequence::KnotSequence(int m, int order) {
	this->order = order;
	inc = 1.0f/(m + this->order - 2);
	createSequence();
}

void KnotSequence::setOrder(int o) {
	order = o;
}

void KnotSequence::setInc(double i) {
	inc = i;
}

int KnotSequence::getOrder() {
	return order;
}

double KnotSequence::getInc() {
	return inc;
}

int KnotSequence::getKnotCount() {
    return (int)knots.size();
}

void KnotSequence::createSequence() {

	if(inc > 1 || inc <= 0) {
		return;
	}

	for(int i = 0; i < order; i++) {
		knots.push_back(0.0f);
	}

	float knotValue = knots[knots.size() - 1] + inc;
	while(floor(knotValue) != 1) {
		knots.push_back(knotValue);
        knotValue = knotValue + inc;
	}

	for(int i = 0; i < order; i++) {
		knots.push_back(1.0f);
	}

}

double KnotSequence::getValue(double u) {
	return knots[ceil(u)];
}

double KnotSequence::getValue(int u) {				
	return knots[u];
}

int KnotSequence::getDelta(double u) {
    for(unsigned int i = 0; i < knots.size() + order - 1; i++) {
        if(u >= knots[i] && u < knots[i+1]) {
            return i;
        }
    }
    return -1;
}
