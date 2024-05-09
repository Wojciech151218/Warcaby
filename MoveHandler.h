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
    Board * board;
	sfEvent* event;
}typedef MoveHandler;

Piece * getPiece(Board board, Square move);
bool equalSquare(Square a, Square b);
Square getCurrentSquare(sfRenderWindow* window, sfEvent * event);
void deselect(MoveHandler * moveHandler);
void handleMove(MoveHandler* moveHandler, sfRenderWindow* window);
void initializeMoveHandler(MoveHandler* moveHandler, sfEvent* event);
