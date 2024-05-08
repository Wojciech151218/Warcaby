#include "Board.h"

Board * getStarterBoard() {
	
	Board * result = (Board*)malloc(sizeof(Board));
	
	int whiteLevel = (BOARD_SIZE - 1) / 2;
	int blackLevel = (BOARD_SIZE - 1) / 2;
	int neutralLevel = 2;
	for (size_t i = 0; i < BOARD_SIZE; i++){
		for (size_t j = 0; j < BOARD_SIZE; j++) {
			if ((i + j) % 2) {
				result->pieces[j][i] = NULL;
				continue;
			}
			if (whiteLevel) {
				result->pieces[j][i] = (Piece*)malloc(sizeof(Piece));
				initializePiece(result->pieces[j][i], White);
				
				continue;
			}
			if (neutralLevel) {
				result->pieces[j][i] = NULL;
				continue;
			}
			if (blackLevel) {
				result->pieces[j][i] = (Piece*)malloc(sizeof(Piece));
				initializePiece(result->pieces[j][i], Black);
			}
		}
		if (whiteLevel) { whiteLevel--;continue; }
		if (neutralLevel) { neutralLevel--;continue; }
		if (blackLevel) { blackLevel--;continue; }
		
	}
	return result;
}
void printBoard(Board board) {
	system("cls");
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			char* c = board.pieces[j][i] != NULL ? "[O]" : "[ ]";
			printf(c);
		}
		printf("\n");
	}
}