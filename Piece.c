#include "Piece.h"
void initializePiece(Piece *piece, PieceColour colour, bool isPromoted) {
	piece->colour = colour;
	piece->isSelected = false;
	piece->isPromoted = isPromoted;
}