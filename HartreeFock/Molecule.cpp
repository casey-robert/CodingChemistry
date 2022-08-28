#include "Molecule.h"

Molecule::Molecule(Atom* atoms, int length)
{
	atomList = new Atom[length];

	//copy the values themselves
	copy(atoms, atoms + length, atomList);
	numAtoms = length;
}

double Molecule::calcNucNucRepEnergyeV()
{

	double totalE = 0;

	for (int i = 0; i < numAtoms; i++)
	{
		for (int j = i + 1; j < numAtoms; j++)
		{
			totalE += (atomList[i].getNucleus().protons * atomList[j].getNucleus().protons) 
				/ findDistance(atomList[i].pos, atomList[j].pos);
		}
	}

	return KE * protonCharge * totalE;
}

double Molecule::calcNucNucRepEnergyJ()
{
	return  Molecule::calcNucNucRepEnergyeV() * protonCharge;
}

double Molecule::calcNucNucRepEnergykJpMol()
{
	return  Molecule::calcNucNucRepEnergyJ() * 1e-3 * N;
}

double Molecule::calcNucNucRepEnergyht()
{

	return  Molecule::calcNucNucRepEnergykJpMol() * 3.8088e-4;
}