#pragma once

#include <string>
#include "Position.h"

class Atom
{
public:
	Position pos;


//Atoms can be defined as H, Li, O, etc or explicit protons and neutrons

	//we give an H and pos 0
	Atom();

	//assumed neutral
	Atom(Position pos, char* ASymbol);
	Atom(Position pos, unsigned short protons, unsigned short neutrons);
	//let them determine #electrons
	Atom(Position pos, char* ASymbol, short electrons);
	Atom(Position pos, unsigned short protons, unsigned short neutrons, unsigne short electrons);








};

