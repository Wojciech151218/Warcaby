#include "Piece.h"
void initializePiece(Piece* piece, PieceColour colour) {
	piece->colour = colour;
	piece->isAlive = true;
	piece->isPromoted = false;
}