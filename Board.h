#pragma once
#include "Piece.h"
#include <stdio.h>
#include "stdlib.h"

struct Board {
	Piece * pieces[BOARD_SIZE][BOARD_SIZE];
} typedef Board;

Board * getStarterBoard();
Board copyBoard(Board board);
void deleteBoard(Board * board);
void printBoardToFile(Board board, FILE *file);
GameState getGameState(Board board);
