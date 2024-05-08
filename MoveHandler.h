#pragma once
#include "Auxilary.h"

struct Move {
	int x, y;
}typedef Move;

struct MoveHandler {
	Move source;
	Move destination;
	bool isSelected;
	bool isDone;
	sfEvent* event;
}typedef MoveHandler;

bool equalMove(Move a, Move b);
Move getCurrentMove(sfRenderWindow* window, sfEvent * event);
void deselect(MoveHandler * moveHandler);
void handleMove(MoveHandler* moveHandler, sfRenderWindow* window);
void initializeMoveHandler(MoveHandler* moveHandler, sfEvent* event);
