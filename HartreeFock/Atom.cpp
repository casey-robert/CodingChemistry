#include "Atom.h"
#include <iostream>
#include <fstream>
#include <unordered_map>


void Atom::loadASymbolValues()
{
	fstream aFile;

	aFile.open("infoFiles/AtomicWeights.txt", ios::in);

	if (aFile.is_open()) {
		string tp;
		while (getline(aFile, tp)) {
			if (tp.length() > 1)
			{
				string aSym = tp.substr(0, tp.find(" "));
				tp = tp.substr(tp.find(" ") + 1, tp.length());

				nucleus currNuc;

				//the proton count
				currNuc.protons = stoi(tp.substr(0, tp.find(" ")));
				tp = tp.substr(tp.find(" ") + 1, tp.length());
				//Neutron count
				currNuc.neutrons = stoi(tp.substr(0, tp.find(" ")));

				Atom::aSymbolMap[aSym] = currNuc;
				Atom::protonMap[currNuc.protons] = aSym;
				//printf("asym %s, proton: %d, neutron %d \n", aSym.c_str(), pNum, nNum);
			}

		}


		aFile.close();
		
		//A method of iterating over a map
		for (pair<string, nucleus> element : aSymbolMap)
		{
			cout << element.first << std::endl;
			cout << element.second.protons << std::endl;
			cout << element.second.neutrons << std::endl;
		}



	}
	else
	{
		printf("HEY I BROKE");
	}

}

Atom::Atom(Position pos, int protons, int neutrons, int electrons)
{
	this->pos = pos;
	//Atom::loadASymbolValues();
	aSymbol = Atom::protonMap[protons];
	nucleus tempNuke;
	tempNuke.protons = protons;
	tempNuke.neutrons = neutrons;
	nuc = tempNuke;
	numElectrons = electrons;
	nucleusMass = nuc.protons * protonMass + nuc.neutrons * neutronMass;
	atomMass = nuc.protons * protonMass + nuc.neutrons * neutronMass + numElectrons * electronMass;
}


//let them determine #e-
Atom::Atom(Position pos, string aSymbol, int electrons)
{
	this->pos = pos;
	this->aSymbol = aSymbol;


	nucleus currNuc;

	//the proton count
	currNuc.protons = 1;
	currNuc.neutrons = 0;



	//Atom::loadASymbolValues();
	nuc = Atom::aSymbolMap[aSymbol];
	numElectrons = electrons;
	nucleusMass = nuc.protons * protonMass + nuc.neutrons * neutronMass;
	atomMass = nuc.protons * protonMass + nuc.neutrons * neutronMass + numElectrons * electronMass;
}




double Atom::getNucleusMass()
{
	return nucleusMass;

}
double Atom::getAtomMass()
{
	return atomMass;
}
string Atom::getASymbol()
{
	return aSymbol;
}
nucleus Atom::getNucleus()
{
	return nuc;
}
int Atom::getNumElectrons()
{
	return numElectrons;
}









