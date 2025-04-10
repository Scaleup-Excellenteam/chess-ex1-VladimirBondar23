#pragma once
#include "Piece.h"
class Cell
{
public:
	Cell(char let, int num, Piece* p) ;
	Cell();
	~Cell();
	char letter;
	int number;
	Piece* piece;

private:
};