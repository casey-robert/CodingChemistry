// HartreeFock.cpp : Defines the entry point for the application.
//

#include "HartreeFock.h"
#include "Atom.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
    Atom test = Atom::Atom(Position::Position(), 3, 4, 3);

	double k = 8.99e9;
	double r = 9.57e-11;
	double n = 6.022e23;
	double kjtoht = 3.8088e-4;
	double jtokj = 1e-3;
	double en = 2 * 8 * 1 * k * protonCharge * protonCharge / r;
	en = en * jtokj * n * kjtoht;
	cout << en << endl;

	return 0;
}
