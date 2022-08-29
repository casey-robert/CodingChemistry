#pragma once

#include "Atom.h"

#define N 6.0221408e23
#define KE  8.98755e9
#define KJPMOLTOHT 3.8088e-4



struct bondingAtom {
	Atom atom;
	int numBonds;
	Atom BondedList[];
};



class Molecule
{

public:
	Atom* atomList;
	int numAtoms;
	

	Molecule(Atom* atoms, int length);

	
	/*Default returns NucNucRepEnergy in J for given Mol*/
	double calcNucNucRepEnergy();
	/* returns NucNucRepEnergy in J, ht, eV, or kJ/mol
		returns in J for unrecognized units*/
	double calcNucNucRepEnergy(string units);

};