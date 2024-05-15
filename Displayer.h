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

void setSelectedPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j);
void setPromotedPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j);
void setPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j);
void setSquare(sfRectangleShape *  rectangleShape,PieceColour pieceColour,int i,int j);
