#include "Molecule.h"

Molecule::Molecule(Atom* atoms, int length)
{
	atomList = new Atom[length];

	//copy the values themselves
	copy(atoms, atoms + length, atomList);
	numAtoms = length;
}

double Molecule::calcNucNucRepEnergy()
{
	return calcNucNucRepEnergy("J");
}
double Molecule::calcNucNucRepEnergy(string units)
{

	double totalE = 0;

	//calculate the repulsion for each atom against each other atom using their charge # and distance
	for (int i = 0; i < numAtoms; i++)
	{
		for (int j = i + 1; j < numAtoms; j++)
		{
			totalE += (atomList[i].getNucleus().protons * atomList[j].getNucleus().protons) 
				/ findDistance(atomList[i].pos, atomList[j].pos);
		}
	}

	//convert to eV units
	totalE = KE * protonCharge * totalE;

	if (units == "eV")
	{
		return totalE;
	}

	//convert to J
	totalE = totalE * protonCharge;

	//technically an unneeded conditional, but kept for readability
	if (units == "J")
	{
		return totalE;
	}

	double jTotalE = totalE;

	//convert to kJ and then kJ/mol via avogadros
	totalE = totalE * 1e-3 * N;

	if (units == "kJ/mol")
	{
		return totalE;
	}

	//convert to hartrees
	totalE = totalE * KJPMOLTOHT;

	if (units == "ht")
	{
		return totalE;
	}
	//return joules if we don't recognize it;
	return jTotalE;
}

