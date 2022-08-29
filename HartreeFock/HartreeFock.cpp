// HartreeFock.cpp : Defines the entry point for the application.
//

#include "HartreeFock.h"
#include "Atom.h"
#include "Position.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	//O
    Atom test = Atom::Atom(Position::Position(), 8, 8, 8);

	Atom list[3] = {Atom::Atom(Position::Position(1,2,3, true), 1, 0, 1), test,
		Atom::Atom(Position::Position(3, -3, 8, true), 1, 0, 1) };


	createAtomTriple(list, 9.57e-11, 9.57e-11, 104.5);
	
	
	Molecule h2O = Molecule(list, 3);

	double energy = h2O.calcNucNucRepEnergy("ht");

	cout << energy << endl;

	cout << h2O.calcNucNucRepEnergy("eV") << endl;


	cout << h2O.calcNucNucRepEnergy() << endl;

	cout << h2O.calcNucNucRepEnergy("kJ/mol") << endl;

	cout << h2O.calcNucNucRepEnergy("ht") << endl;
	return 0;
}


/*
* SOME CODE FOR testing position mod functions
	printf("0th: x: %lf y %lf z: %lf\n 1th: x: %lf y %lf z: %lf\n 2th: x: %lf y %lf z: %lf\n  Dist01: %lf\n Dist12: %lf\n",
		list[0].pos.x, list[0].pos.y, list[0].pos.z, list[1].pos.x, list[1].pos.y, list[1].pos.z,
		list[2].pos.x, list[2].pos.y, list[2].pos.z,
		findDistance(list[1].pos, list[0].pos), findDistance(list[1].pos, list[2].pos));

	createAtomTriple(list, 9.57e-11, 9.57e-11, 104.5);


	printf("0th: x: %lf y %lf z: %lf\n 1th: x: %lf y %lf z: %lf\n 2th: x: %lf y %lf z: %lf\n  Dist01: %lf\n Dist12: %lf\n",
		list[0].pos.x, list[0].pos.y, list[0].pos.z, list[1].pos.x, list[1].pos.y, list[1].pos.z,
		list[2].pos.x, list[2].pos.y, list[2].pos.z,
		findDistance(list[1].pos, list[0].pos), findDistance(list[1].pos, list[2].pos));
	*/
