#include "Atom.h"
#include <iostream>
#include <fstream>


Atom::Atom()
{
	Position center = Position::Position();
	Atom(center, "H");

}



Atom::Atom(Position pos, string aSymbol)
{
	this->pos = pos;
	this->aSymbol = aSymbol;
	Atom::loadASymbolValues();

}


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
				int nucleusNum[2];
				//the proton count
				nucleusNum[0] = stoi(tp.substr(0, tp.find(" ")));
				tp = tp.substr(tp.find(" ") + 1, tp.length());
				//Neutron count
				nucleusNum[1] = stoi(tp.substr(0, tp.find(" "))); 

				aSymbolMap.insert(aSym, nucleusNum);

				//printf("asym %s, proton: %d, neutron %d \n", aSym.c_str(), pNum, nNum);
			}
			
		}
		aFile.close(); 
	}
	else
	{
		printf("HEY I BROKE");
	}

}




