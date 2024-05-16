#pragma once
#include "Board.h"
#include "Auxilary.h"
#include "MoveHandler.h"

struct Displayer{
	Board * board;
    sfRenderWindow * window;

} typedef Displayer;

Displayer getDisplayer(Board *board, sfRenderWindow *window);
void display(Displayer *displayer);

void setSelectedPiece(sfSprite *sprite, PieceColour pieceColour, int i, int j);
void setPromotedPiece(sfSprite *sprite, PieceColour pieceColour, int i, int j);
void setPiece(sfSprite *sprite, PieceColour pieceColour, int i, int j);
void setSquare(sfRectangleShape *  rectangleShape,PieceColour pieceColour,int i,int j);
