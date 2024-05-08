#pragma once
#include "Piece.h"
#include <stdio.h>

struct Board {
	Piece * pieces[BOARD_SIZE][BOARD_SIZE];
} typedef Board;

Board * getStarterBoard();
void printBoard(Board board);
