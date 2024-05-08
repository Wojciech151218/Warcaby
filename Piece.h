#pragma once
#include "Auxilary.h"

struct Piece{
	bool isAlive;
	bool isPromoted;
	enum PieceColour colour;


} typedef Piece;
void initializePiece(Piece* piece,PieceColour colour);