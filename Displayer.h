#pragma once
#include "Board.h"
#include "Auxilary.h"
#include "MoveHandler.h"

struct Displayer{
	Board * board;

} typedef Displayer;

Displayer initialize(Board * board);
void display(Displayer displayer, sfRenderWindow* window,MoveHandler moveHandler);