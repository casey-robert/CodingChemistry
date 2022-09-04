#include "Atom.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Position.h"

#define PI 3.14159

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


void createAtomTriple(Atom* atoms, double lDist, double rDist, double bondAngle)
{
	double centralx = atoms[1].pos.x;
	double centraly = atoms[1].pos.y;
	double centralz = atoms[1].pos.z;

	//define the left atom's pos
	atoms[0].pos.x = centralx - lDist;
	atoms[0].pos.y = centraly;
	atoms[0].pos.z = centralz;

	
	
	//set to <=180.0
	bondAngle = 180 - fmod(bondAngle, 180.0);//bondAngle - ((int)bondAngle / 180) * 180.0;
	//cout << bondAngle << endl;
	// converting degrees to radians
	bondAngle = bondAngle * PI / 180.0;

	//define right atom's pos
	atoms[2].pos.x = centralx + rDist * sin(bondAngle);
	atoms[2].pos.y = centraly + rDist * cos(bondAngle);
	atoms[2].pos.z = centralz;

	//update the spher for changed pos
	atoms[0].pos.updateSpher();
	atoms[2].pos.updateSpher();
	
	




}

void modifybondLength(Atom* atoms, double delta)
{
	//we find the x y and z direction of the bond between the 2;
	double xdir = atoms[1].pos.x - atoms[0].pos.x;
	double ydir = atoms[1].pos.y - atoms[0].pos.y;
	double zdir = atoms[1].pos.z - atoms[0].pos.z;

	double bondDist = findDistance(atoms[0].pos, atoms[1].pos);
	double newBondDist = bondDist + delta;
	
	double modFactor = newBondDist / bondDist;//sqrt(newBondDist / bondDist);

	atoms[1].pos.x = atoms[0].pos.x + xdir * modFactor;
	atoms[1].pos.y = atoms[0].pos.y + ydir * modFactor;
	atoms[1].pos.z = atoms[0].pos.z + zdir * modFactor;

	//update the spherical to match
	atoms[1].pos.updateSpher();
	atoms[0].pos.updateSpher();

	//cout << newBondDist << endl;
	//cout << findDistance(atoms[0].pos, atoms[1].pos) << endl;

}


void modifybondAngle(Atom* atoms, double delta)
{
	// we find the x y and z direction of the bond between the 0 and 1;
	double xdir01 = atoms[1].pos.x - atoms[0].pos.x;
	double ydir01 = atoms[1].pos.y - atoms[0].pos.y;


	// we find the x y and z direction of the bond between the 1 and 2;
	double xdir12 = atoms[2].pos.x - atoms[1].pos.x;
	double ydir12 = atoms[2].pos.y - atoms[1].pos.y;

	//make a line for a0 and a1
	double m = ydir01 / xdir01;
	double b = atoms[0].pos.y - m * atoms[0].pos.x;

	double dist12 = findxyDist(atoms[1].pos, atoms[2].pos);

	//double oldAngle = acos((side01 * side01 + side12 * side12 - side02 * side02) / (2 * side01 * side02));
	double deltaRad = delta * PI / 180.0;
	double oldAngle = atan(ydir12 / xdir12);
	cout << "OLD ANGLE: " << oldAngle * 180.0 / PI << endl;
	double newAngle = oldAngle;

	//add or subtract the delta based on if the atom is above or below the 01 atom line
	(atoms[2].pos.y > (m * atoms[2].pos.x + b)) ? (newAngle += deltaRad) : (newAngle -= deltaRad);
	
	cout << "NEW ANGLE: " << newAngle * 180.0 / PI << endl;

	cout << "SIN: " << sin(oldAngle) << endl;
	cout << "Cos: " << cos(oldAngle) << endl;
	double newdy = dist12 * sin(newAngle);
	double newdx = dist12 * cos(newAngle);

	atoms[2].pos.x = atoms[1].pos.x + newdx;
	atoms[2].pos.y = atoms[1].pos.y + newdy;

	//update the spherical to match
	//atoms[1].pos.updateSpher();
	//atoms[0].pos.updateSpher();

	//cout << newBondDist << endl;
	//cout << findDistance(atoms[0].pos, atoms[1].pos) << endl;
}


double bondAngle(Atom* atoms)
{
	double side01 = findDistance(atoms[0].pos, atoms[1].pos);
	double side12 = findDistance(atoms[2].pos, atoms[1].pos);
	double side02 = findDistance(atoms[2].pos, atoms[0].pos);
	//give the inner angle
	 
	return 180.0 * acos((side01 * side01 + side12 * side12 - side02 * side02) / (2 * side01 * side12)) / PI;
	//double oldAngle = acos((side01 * side01 + side12 * side12 - side02 * side02) / (2 * side01 * side02));
}





