#include "Piece.h"
void initializePiece(Piece* piece, PieceColour colour) {
	piece->colour = colour;
	piece->isSelected = false;
	piece->isPromoted = false;
}