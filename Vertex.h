 #ifndef _VERTEX_H_
 #define _VERTEX_H_

/*
 * CPSC 589
 *
 * vertex class
 *  - represents vertex that forms the curve.
 *
 *
 * Sean Brown
 *
 */

class Vertex {
	
protected:
	double x, y, z;

public:
	Vertex();
	Vertex(double, double, double);

	Vertex operator*(double);
	Vertex operator+(Vertex);

	double getX();
	double getY();
	double getZ();

	void setX(double);
	void setY(double);
	void setZ(double);

};

#endif