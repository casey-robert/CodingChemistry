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
				nucleus currNuc;

				//the proton count
				currNuc.protons = stoi(tp.substr(0, tp.find(" ")));
				tp = tp.substr(tp.find(" ") + 1, tp.length());
				//Neutron count
				currNuc.neutrons = stoi(tp.substr(0, tp.find(" "))); 

				aSymbolMap[aSym] = currNuc;
				//printf("asym %s, proton: %d, neutron %d \n", aSym.c_str(), pNum, nNum);
			}
			
		}
	
		/*
		A method of iterating over a map
		for (pair<string, nucleus> element : aSymbolMap)
		{
			cout << element.first << std::endl;
			cout << element.second.protons << std::endl;
			cout << element.second.neutrons << std::endl;
		}*/

		
		aFile.close(); 
	}
	else
	{
		printf("HEY I BROKE");
	}

}




