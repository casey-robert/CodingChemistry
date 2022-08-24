// HartreeFock.cpp : Defines the entry point for the application.
//

#include "HartreeFock.h"
#include "Atom.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	Atom test = Atom::Atom();

	double k = 8.99e9;
	double r = 9.57e-11;

	double en = 2 * 8 * 1 * k * protonCharge * protonCharge / r;

	//cout << en << endl;

	return 0;
}
