#include "Auxilary.h"
#include "MoveHandler.h"
#include "Board.h"

struct GameLogicHandler {
	Board * board;
} typedef GameLogicHandler;

void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board);
bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler);
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler * moveHandler);