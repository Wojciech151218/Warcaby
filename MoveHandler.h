#pragma once
#include "Auxilary.h"
#include "Board.h"



struct MoveHandler {
	Square source;
	Square destination;
    Piece * pieceSelected;
    bool isFinished;
	sfEvent* event;
}typedef MoveHandler;

Piece * getPiece(Board board, Square move);


int distanceBetweenSquares(Square a, Square b);

Square getCurrentSquare(sfRenderWindow* window, sfEvent * event);
void deselect(MoveHandler * moveHandler);
void updateAfterCapture(MoveHandler *moveHandler, Square newSource);
void handleMove(MoveHandler *moveHandler, sfRenderWindow *window, Board board, PieceColour turn);
void initializeMoveHandler(MoveHandler* moveHandler, sfEvent* event);
