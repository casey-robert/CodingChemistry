#include "Position.h"


Position::Position()
{
	//position is the center
	x = 0;
	y = 0;
	z = 0;
	
	r = 0;
	theta = 0;
	phi = 0;


}

Position::Position(double v1, double v2, double v3, bool cartesian)
{
	if (cartesian)
	{
		this->x = v1;
		this->y = v2;
		this->z = v3;
		updateSpher();
	}
	else
	{
		r = v1;
		theta = v2; 
		phi = v3;
		updateCart();
	}
}

void Position::updateCart()
{
		x = r * sin(phi) * cos(theta);
		y = r * sin(phi) * sin(theta);
		z = r * cos(phi);
}

void Position::updateSpher()
{
	
		r = sqrt(x * x + y * y + z * z);
		theta = atan(x / y);
		phi = acos(z / r);

}

double Position::length()
{
	
		return sqrt(x*x+y*y+z*z);
	
		//return r;
	
}


void Position::normalize()
{
	
	double l = length();
	x = x / l;
	y = y / l;
	z = z / l;
	//sphere norm
	r = 1;
	
}



double findDistance(Position a, Position b)
{
	
	//in case the cartesian side needs to be updated
	//a.updateCart();
	//b.updateCart();
	double d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));

	return d;

}
