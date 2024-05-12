#pragma once
#include "Auxilary.h"
#include "Board.h"

struct Square {
	int x, y;
}typedef Square;
enum MoveState{
    Pending,Selected,Finished
}typedef MoveState;

struct MoveHandler {
	Square source;
	Square destination;
    Piece * pieceSelected;
    bool isFinished;
	sfEvent* event;
}typedef MoveHandler;

Piece * getPiece(Board board, Square move);


bool equalSquare(Square a, Square b);
bool isSquareOnTheBoard(Square square);
Square minusSquare(Square a, Square b);
Square plusSquare(Square a, Square b);
Square multiplySquare(Square a,int factor);
int distanceBetweenSquares(Square a, Square b);

Square getCurrentSquare(sfRenderWindow* window, sfEvent * event);
void deselect(MoveHandler * moveHandler);
void handleMove(MoveHandler *moveHandler, sfRenderWindow *window, Board board, PieceColour turn);
void initializeMoveHandler(MoveHandler* moveHandler, sfEvent* event);
