#pragma once
#include <cmath>


class Position
{
public:


	bool cartesian;

	//Cartesian
	double x;
	double y;
	double z;

	//Spherical
	double r;
	double theta;
	double phi;


	Position();

	Position(double v1, double v2, double v3, bool cartesian);

	void convToCart();


	void convToSpher();


	double length();

	void normalize();

};

static double findDistance(Position a, Position b);



