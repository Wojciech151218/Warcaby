#include "GameLogicHandler.h"

void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board) {
	gameLogicHandler->board = board;
}

bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler) {
	


	return moveHandler.isFinished;
}
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler * moveHandler) {
	Square source = moveHandler->source;
	Square destination = moveHandler->destination;
    deselect(moveHandler);

	Piece* sPiece = gameLogicHandler->board->pieces[source.x][source.y];
	gameLogicHandler->board->pieces[source.x][source.y] = NULL;
	gameLogicHandler->board->pieces[destination.x][destination.y] = sPiece;

}