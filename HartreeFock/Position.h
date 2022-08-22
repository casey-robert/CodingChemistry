#pragma once
#include <cmath>


class Position
{
public:


	bool cartesian = false;

	//Cartesian
	double x = 0;
	double y = 0;
	double z = 0;

	//Spherical
	double r = 0;
	double theta = 0;
	double phi = 0;


	Position();

	Position(double v1, double v2, double v3, bool cartesian);

	void convToCart();


	void convToSpher();


	double length();

	void normalize();

};

static double findDistance(Position a, Position b);



