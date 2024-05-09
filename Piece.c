#include "Piece.h"
void initializePiece(Piece* piece, PieceColour colour) {
    printf("piece initialized\n");
	piece->colour = colour;
	piece->isSelected = false;
	piece->isPromoted = false;
}