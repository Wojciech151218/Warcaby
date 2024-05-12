#pragma once
#include "Board.h"
#include "Auxilary.h"
#include "MoveHandler.h"

struct Displayer{
	Board * board;

} typedef Displayer;

Displayer initialize(Board * board);
void display(Displayer displayer, sfRenderWindow* window,MoveHandler moveHandler);
void setSelectedPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j);
void setPromotedPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j);
void setPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j);
void setSquare(sfRectangleShape *  rectangleShape,PieceColour pieceColour,int i,int j);