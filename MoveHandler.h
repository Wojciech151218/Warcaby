#pragma once
#include "Auxilary.h"

struct Move {
	int x, y;
}typedef Move;

struct MoveHanlder {
	Move source;
	Move destination;
	bool isSelected;
	bool isDone;
	sfEvent* event;
}typedef MoveHandler;

bool equalMove(Move a, Move b);
Move getCurrentMove(sfRenderWindow* window, sfEvent * event);
void deselect(MoveHandler * moveHanlder);
void handleMove(MoveHandler* moveHanlder, sfRenderWindow* window);
void initializeMoveHandler(MoveHandler* moveHandler, sfEvent* event);
