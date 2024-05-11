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
Board copyBoard(Board board){
    Board result;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j)
            result.pieces[i][j] = board.pieces[i][j];
    }
    return result;
}
void deleteBoard(Board * board){
    if(!board) return;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if(!board->pieces[i][j]) continue;
            free(board->pieces[i][j]);
            board->pieces[i][j] = NULL;
        }
    }
}

void printBoard(Board board) {//TODO można to zmodyfikowac w zapisywacz plików
	system("cls");
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			Piece * piece = board.pieces[j][i] ;
			printf("[%x]",piece);
		}
		printf("\n");
	}
}