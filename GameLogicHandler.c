#include "GameLogicHandler.h"

void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board) {
	gameLogicHandler->board = board;
}


bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler) {
	


	return moveHandler.isFinished;
}

void capture(GameLogicHandler * gameLogicHandler, Square square){

    gameLogicHandler->board->pieces[square.x][square.y] = NULL;
}
void makeMove(GameLogicHandler * gameLogicHandler,Square source, Square destination){
    Piece* sPiece = gameLogicHandler->board->pieces[source.x][source.y];
    gameLogicHandler->board->pieces[source.x][source.y] = NULL;
    gameLogicHandler->board->pieces[destination.x][destination.y] = sPiece;
}
void captureMove(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler){
    Square source = moveHandler.source;
    Square destination = moveHandler.destination;


    bool topRight = source.x == destination.x+2 && source.y == destination.y +2 ;
    bool topLeft = source.x == destination.x-2 && source.y == destination.y +2;
    bool downRight = source.x == destination.x+2 && source.y == destination.y -2;
    bool downLeft = source.x == destination.x-2 && source.y == destination.y -2;


    if (!(topLeft||topRight||downLeft||downRight)) return;

    Piece * sourcePiece = getPiece(*gameLogicHandler->board,source);
    Piece * destinationPiece = getPiece(*gameLogicHandler->board,destination);

    if(!sourcePiece || destinationPiece) return;

    Square  capturedSquare =  plusSquare(source, minusSquare(destination,source));
    Piece * capturedPiece = getPiece(*gameLogicHandler->board,capturedSquare);

    if(!capturedPiece)return;
    capture(gameLogicHandler,capturedSquare);
    makeMove(gameLogicHandler,source,destination);


}
void slideMove(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler){
    Square source = moveHandler.source;
    Square destination = moveHandler.destination;


    bool topRight = source.x == destination.x+1 && source.y == destination.y +1 ;
    bool topLeft = source.x == destination.x-1 && source.y == destination.y +1;
    bool downRight = source.x == destination.x+1 && source.y == destination.y -1;
    bool downLeft = source.x == destination.x-1 && source.y == destination.y -1;

    if (!(topLeft||topRight||downLeft||downRight)) return;
    Piece * sourcePiece = getPiece(*gameLogicHandler->board,source);
    Piece * destinationPiece = getPiece(*gameLogicHandler->board,destination);

    if(!sourcePiece || destinationPiece) return;
    makeMove(gameLogicHandler,source,destination);


}
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler * moveHandler) {
    slideMove(gameLogicHandler,*moveHandler);
    captureMove(gameLogicHandler,*moveHandler);
    deselect(moveHandler);

}