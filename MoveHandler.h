#pragma once
#include "Auxilary.h"

struct Move {
	int x, y;
}typedef Move;
enum MoveState{
    Pending,Selected,Finished
}typedef MoveState;

struct MoveHandler {
	Move source;
	Move destination;
    MoveState moveState;
	sfEvent* event;
}typedef MoveHandler;

bool equalMove(Move a, Move b);
Move getCurrentMove(sfRenderWindow* window, sfEvent * event);
void deselect(MoveHandler * moveHandler);
void handleMove(MoveHandler* moveHandler, sfRenderWindow* window);
void initializeMoveHandler(MoveHandler* moveHandler, sfEvent* event);
