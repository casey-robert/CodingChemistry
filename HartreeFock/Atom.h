#pragma once

#include <string>
#include "Position.h"
#include <unordered_map>
#include "Position.h"
#include <cmath>

using namespace std;
//in units kg
static const double protonMass = 1.672622e-27;
static const double neutronMass = 1.674927e-27;
static const double electronMass = 9.109384e-31;
//in amu 
static const double protonMassAMU = 1.007316;
static const double neutronMassAMU = 1.008701;
static const double electronMassAMU = 0.000549;
static const double convAMUtokg = 1.6605e-27;

//proton electron charge in units C, 
static const double protonCharge = 1.602176634e-19;
static const double electronCharge = -1.602176634e-19;

struct nucleus {
	int protons;
	int neutrons;
};






class Atom
{
private:
	//we make private the things the user shouldn't be able to edit, but we allow them to access it via a getter
	double nucleusMass;
	double atomMass;
	string aSymbol;
	nucleus nuc;
	int numElectrons;


	/*gives the #protons and neutrons given an atomic symbol*/
	unordered_map<string, nucleus> aSymbolMap;
	/*gives the aSymbol given a # of protons*/
	static unordered_map<int, string> protonMap;

	/*used to load in a text file that connects # Protons and Neutrons to an Atomic Symbol such as H, He, Li, etc*/
	void loadASymbolValues();
public:
	/*we make public all of our accessible methods and variable(s)*/
	Position pos;

	/*Atoms can be defined as H, Li, O, etc or explicit protons and neutrons
	the most common isotope is used if the symbol is given */
	
	//we give an H and pos 0 when no input given
	Atom() : Atom(Position::Position(), "H") {}

	/*we count using unsigned short
	technically an unsigned char could be used, but I didn't want to have possible summation issues down the road*/

	//assumed neutral
	Atom(Position pos, string aSymbol) : Atom(pos, aSymbol, aSymbolMap[aSymbol].protons) {
		Atom::loadASymbolValues();
	}
	Atom(Position pos, int protons, int neutrons) : Atom(pos, protons, neutrons, protons) {}
	//let them determine #e-
	Atom(Position pos, string aSymbol, int electrons);
	Atom(Position pos, int protons, int neutrons, int electrons);


	//Our getters
	double getNucleusMass();
	double getAtomMass();
	string getASymbol();
	nucleus getNucleus();
	int getNumElectrons();



};

