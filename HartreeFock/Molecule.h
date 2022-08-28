#pragma once

#include "Atom.h"

#define N 6.0221408e23
#define KE  8.98755e9




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
	//returns value in joules
	double calcNucNucRepEnergyht();
	double calcNucNucRepEnergykJpMol();
	double calcNucNucRepEnergyJ();
	double calcNucNucRepEnergyeV();



};