 #ifndef _VERTEX_H_
 #define _VERTEX_H_

/*
 * vertex class
 *  - represents vertex that forms the curve.
 *
 * From CPSC 589
 *
 * Sean Brown
 *
 */

 #include <math.h>
 #include <stdio.h>

class Vertex {
	
protected:
	double x, y, z;

public:
	Vertex();
	Vertex(double, double, double);

	Vertex operator*(double);
	Vertex operator+(Vertex);
	Vertex operator-(Vertex);

	double getX();
	double getY();
	double getZ();

	void setX(double);
	void setY(double);
	void setZ(double);

	static Vertex crossProduct(Vertex, Vertex);
	static double dotProduct(Vertex, Vertex);

	double length();
	void normalize();
  
  void print();

};

#endif
