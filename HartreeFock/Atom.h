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
	unordered_map<int, string> protonMap;

	/*used to load in a text file that connects # Protons and Neutrons to an Atomic Symbol such as H, He, Li, etc*/
	void loadASymbolValues();

public:
	/*we make public all of our accessible methods and variable(s)*/
	Position pos;

	/*Atoms can be defined as H, Li, O, etc or explicit protons and neutrons
	the most common isotope is used if the symbol is given */
	
	//we give an H and pos 0 when no input given
	
	Atom() : Atom(Position::Position(), 1, 0, 1) {};
	
	/*we count using unsigned short
	technically an unsigned char could be used, but I didn't want to have possible summation issues down the road*/

	//assumed neutral
	
	Atom(Position pos, string aSymbol) : Atom(pos, aSymbol, aSymbolMap[aSymbol].protons) {};
	Atom(Position pos, int protons, int neutrons) : Atom(pos, protons, neutrons, protons) {};
	
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
/*Takes 3 atoms and uses the central atom as an anchor, takes the first and last and creates the established bond lengths and angle
the first atom is established in the x plane and the third creates the angle in y, z plane is whatever the central atom has
*/
void createAtomTriple(Atom* atoms, double lDist, double rDist, double bondAngle);


/* change bond length by given delta
uses array so no return is required
changes the locations of the second passed atom*/
void modifybondLength(Atom* atoms, double delta);



/*
Modify Bond angle
 modify the angle between 3 given atoms
 atom 0 and 1 remain identical, angle shifted through atom #2
*/
void modifybondAngle(Atom* atoms, double delta);


/*
* return the inner angle of 3 atoms in the xy plane
*/
double bondAngle(Atom* atoms);
/*TODO if wanted/helpful
 Takes 4 atoms and modifies the dihedral angle centered on the */
//static Atom* dihedralAngle();
