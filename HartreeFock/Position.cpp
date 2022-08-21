#include "Position.h"


Position::Position()
{
	x = 0;
	y = 0;
	z = 0;
	//default to cartesian
	cartesian = true;

}

Position::Position(double v1, double v2, double v3, bool cartesian)
{
	if (cartesian)
	{
		this->x = v1;
		this->y = v2;
		this->z = v3;
		this->cartesian = true;
	}
	else
	{
		r = v1;
		theta = v2; 
		phi = v3;
		cartesian = false;
	}
}

void Position::convToCart()
{
	if (!cartesian)
	{
		x = r * sin(phi) * cos(theta);
		y = r * sin(phi) * sin(theta);
		z = r * cos(phi);
		cartesian = true;
	}
}

void Position::convToSpher()
{
	if (cartesian)
	{
		r = length();
		theta = atan(x / y);
		phi = acos(z / r);
		cartesian = false;
	}
}

double Position::length()
{
	if (cartesian)
	{
		return sqrt(x*x+y*y+z*z);
	}
	else
	{
		return r;
	}
}


void Position::normalize()
{
	if (cartesian)
	{
		double l = length();
		x = x / l;
		y = y / l;
		z = z / l;
	}
	else
	{
		r = 1;
	}
}



static double findDistance(Position a, Position b)
{
	/*first we conv to cart then calc
	This is easier, as calculating the distance staying in spherical is simply inserting the spherical-cart conversions into
	the equation*/
	
	bool aOrig = a.cartesian;
	bool bOrig = b.cartesian;
	a.convToCart();
	b.convToCart();

	double d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));

	if (!aOrig)
	{
		a.convToSpher();
	}
	if (!bOrig)
	{
		b.convToSpher();
	}

	return d;

}
