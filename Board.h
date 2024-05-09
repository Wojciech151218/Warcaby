#pragma once
#include "Piece.h"
#include <stdio.h>

struct Board {
	Piece * pieces[BOARD_SIZE][BOARD_SIZE];
} typedef Board;

Board * getStarterBoard();
Board copyBoard(Board board);
void printBoard(Board board);
