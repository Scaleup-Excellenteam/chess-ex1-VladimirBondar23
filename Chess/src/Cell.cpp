#include "Cell.h"

Cell::Cell(char let, int num, Piece* p) : letter (let),number(num), piece(p)
{
}

Cell::Cell() : Cell(0,0,nullptr)
{
	
}

Cell::~Cell()
{
}