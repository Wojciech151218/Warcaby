#include "GameLogicHandler.h"

void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board) {
	gameLogicHandler->board = board;
}
bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler) {
	
	Move source = moveHandler.source;
	Move destination = moveHandler.destination;
	Piece* sourcePiece = gameLogicHandler->board->pieces[source.x][source.y];
	
	return moveHandler.isDone &&  sourcePiece != NULL;
}
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler moveHandler) {
	Move source = moveHandler.source;
	Move destination = moveHandler.destination;

	Piece* sPiece = gameLogicHandler->board->pieces[source.x][source.y];
	gameLogicHandler->board->pieces[source.x][source.y] = NULL;
	gameLogicHandler->board->pieces[destination.x][destination.y] = sPiece;

}