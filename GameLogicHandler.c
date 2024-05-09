#include "GameLogicHandler.h"

void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board) {
    printf("GameLogicHandler initialized\n");
	gameLogicHandler->board = board;
    gameLogicHandler->turn = White;
}



bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler) {
	


	return moveHandler.isFinished;
}
bool isMoveForward(MoveDirection moveDirection,PieceColour pieceColour){
    bool forwardForBlack = (moveDirection == TopRight || moveDirection == TopLeft) &&pieceColour==Black;
    bool forwardForWhite =( moveDirection == DownRight || moveDirection == DownLeft)&&pieceColour==White;

    return forwardForWhite || forwardForBlack;
}

void capture(GameLogicHandler * gameLogicHandler, Square square){

    gameLogicHandler->board->pieces[square.x][square.y] = NULL;
}
Square getFirstOccupiedSquare(GameLogicHandler gameLogicHandler,Square squares[]){
    for (int i = 0; i < BOARD_SIZE; ++i)
        if(gameLogicHandler.board->pieces[squares[i].x][squares[i].y]) return squares[i];
    perror("didnt find an occupied square");
}

void getSquaresBetween(GameLogicHandler * gameLogicHandler, Square  squares[],Square  source , Square destination,MoveDirection moveDirection){
    Square step = getSquareFromMoveDirection(moveDirection);
    Square currentSquare = plusSquare(source,step);
    int i=0;
    while (!equalSquare(currentSquare,destination)){

        squares[i++] = currentSquare;
        currentSquare = plusSquare(currentSquare,step);
    }

}
int howManyPieces(GameLogicHandler gameLogicHandler,Square  squares[],int moveDistance){
    int result =0;
    for (int i = 0; i < moveDistance; ++i)
        result += getPiece(*gameLogicHandler.board,squares[i]) ? 1:0;
    return result;
}
MoveDirection getMoveDirection(Square source , Square destination, int moveDistance){// TODO widzi ruchy jako udany tylko gdy jest wykonany na makszymalna długosc nie akceptuje przedziałow
    if(source.x == destination.x+moveDistance && source.y == destination.y +moveDistance) return TopRight;
    if(source.x == destination.x-moveDistance && source.y == destination.y +moveDistance) return TopLeft;
    if(source.x == destination.x+moveDistance && source.y == destination.y -moveDistance) return DownRight;
    if(source.x == destination.x-moveDistance && source.y == destination.y -moveDistance) return DownLeft;
    return Failed;
}
Square getSquareFromMoveDirection(MoveDirection moveDirection){
    switch (moveDirection) {
        case TopRight:
            return (Square){-1,-1};
        case TopLeft:
            return (Square){1,-1};
        case DownRight:
            return (Square){-1,1};
        case DownLeft:
            return (Square){1,1};
        default:
            return (Square){0,0};
    }
};



void makeMove(GameLogicHandler * gameLogicHandler,Square source, Square destination){
    Piece* sPiece = gameLogicHandler->board->pieces[source.x][source.y];
    gameLogicHandler->board->pieces[source.x][source.y] = NULL;
    gameLogicHandler->board->pieces[destination.x][destination.y] = sPiece;
}
void captureMove(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler){
    Square source = moveHandler.source;
    Square destination = moveHandler.destination;
    
    Piece * sourcePiece = getPiece(*gameLogicHandler->board,source);
    Piece * destinationPiece = getPiece(*gameLogicHandler->board,destination);
    if(!sourcePiece || destinationPiece) return;

    int pieceRange = sourcePiece->isPromoted ? BOARD_SIZE : 2 ;
    int moveDistance = distanceBetweenSquares(source,destination);
    if(pieceRange>moveDistance)return;

    MoveDirection moveDirection = getMoveDirection(source,destination,pieceRange);//TODO zmienic piecerange na move distance
    if (moveDirection==Failed) return;

    Square squaresBetween[moveDistance-1];
    getSquaresBetween(gameLogicHandler,squaresBetween,source,destination,moveDirection);
    if(howManyPieces(*gameLogicHandler,squaresBetween,moveDistance)!=1)return;

    Square capturedSquare = getFirstOccupiedSquare(*gameLogicHandler,squaresBetween);
    capture(gameLogicHandler,capturedSquare);
    makeMove(gameLogicHandler,source,destination);


}
void slideMove(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler){
    Square source = moveHandler.source;
    Square destination = moveHandler.destination;

    Piece * sourcePiece = getPiece(*gameLogicHandler->board,source);
    Piece * destinationPiece = getPiece(*gameLogicHandler->board,destination);
    if(!sourcePiece || destinationPiece) return;

    int pieceRange = sourcePiece->isPromoted ? BOARD_SIZE : 1 ;
    int moveDistance = distanceBetweenSquares(source,destination);
    if(pieceRange>moveDistance)return;

    MoveDirection moveDirection = getMoveDirection(source,destination,pieceRange);//TODO zmienic piecerange na move distance
    if (moveDirection==Failed || !isMoveForward(moveDirection,sourcePiece->colour)) return;

    Square squaresBetween[moveDistance-1];
    getSquaresBetween(gameLogicHandler,squaresBetween,source,destination,moveDirection);
    if(howManyPieces(*gameLogicHandler,squaresBetween,moveDistance)!=0)return;

    makeMove(gameLogicHandler,source,destination);


}
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler * moveHandler) {
    slideMove(gameLogicHandler,*moveHandler);
    captureMove(gameLogicHandler,*moveHandler);
    deselect(moveHandler);

}