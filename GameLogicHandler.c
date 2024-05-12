#include "GameLogicHandler.h"

void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board, PieceColour turn) {
	gameLogicHandler->board = board;
    gameLogicHandler->turn = turn;
}
GameLogicHandler copyGameLogicHandler(GameLogicHandler gameLogicHandler){
    GameLogicHandler result;
    Board copiedBoard = copyBoard(*gameLogicHandler.board);
    initializeGameLogicHandler(&result,&copiedBoard,gameLogicHandler.turn);
    return result;
}
void deleteGameLogicHandler(GameLogicHandler * gameLogicHandler){
    //deleteBoard(gameLogicHandler->board);
    //free(gameLogicHandler);
    //gameLogicHandler = NULL;
}
bool test(GameLogicHandler * gameLogicHandler, MoveHandler * moveHandler){
    if(!moveHandler->isFinished) return false;
    if(slideMove(gameLogicHandler,moveHandler->source,moveHandler->destination)
    || captureMove(gameLogicHandler,moveHandler->source,moveHandler->destination))
        return true;

    deselect(moveHandler);
    return false;
}

bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler * moveHandler) {
    if(!moveHandler->isFinished) return false;

    int preMoveCaptureCount = getMaxCapture(*gameLogicHandler);
    if(!preMoveCaptureCount){// jesli nie ma bic
        if(slideMove(gameLogicHandler,moveHandler->source,moveHandler->destination)) return true;
        deselect(moveHandler);
        return false;
    }
    GameLogicHandler * moveTester = malloc( sizeof(GameLogicHandler)) ;// jakims chujem Move tester zapisany na stosie się dziwnie zachowuje a ten na kopcu działa dobrze
    Board copiedBoard = copyBoard(*gameLogicHandler->board);
    initializeGameLogicHandler(moveTester,&copiedBoard,gameLogicHandler->turn);

    if(!captureMove(moveTester,moveHandler->source,moveHandler->destination)){//jesli sa bicia ale ruch jest nieprawidłwoy np nie jest biciem
        free(moveTester);
        deselect(moveHandler);
        return false;
    }
    int postMoveCaptureCount = getMaxCapture(*moveTester);
    free(moveTester);

    if(postMoveCaptureCount+1 == preMoveCaptureCount){//jesli wybierzemy najsilniejsze bicie
        captureMove(gameLogicHandler,moveHandler->source,moveHandler->destination);
        return !postMoveCaptureCount;
    }
    return false; //jesli wybierzemy słabsze bicie;
}
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler * moveHandler) {
    if(isSquarePromotable(gameLogicHandler,moveHandler->destination))
        promote(gameLogicHandler,moveHandler->destination);
    gameLogicHandler->turn = !gameLogicHandler->turn;
    deselect(moveHandler);
}
bool isMoveForward(MoveDirection moveDirection,PieceColour pieceColour){
    bool forwardForBlack = (moveDirection == TopRight || moveDirection == TopLeft) &&pieceColour==Black;
    bool forwardForWhite = (moveDirection == DownRight || moveDirection == DownLeft)&&pieceColour==White;
    return forwardForWhite || forwardForBlack;
}
bool isSquarePromotable(GameLogicHandler * gameLogicHandler,Square square){
    Piece * promotedPiece = getPiece(*gameLogicHandler->board,square);
    PieceColour pieceColour = promotedPiece->colour;
    bool forWhite = square.y==BOARD_SIZE-1 && pieceColour == White;
    bool forBlack = square.y == 0 && pieceColour == Black;
    return forBlack || forWhite;
}

int getPieceRange(Piece piece,bool slide){
    return piece.isPromoted ? BOARD_SIZE : slide ? 1:2 ;
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
    for (int i = 0; i < moveDistance-1; ++i)
        result += getPiece(*gameLogicHandler.board,squares[i]) ? 1:0;
    return result;
}
MoveDirection getMoveDirection(Square source , Square destination, int moveDistance){
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
    Piece* sourcePiece = getPiece(*gameLogicHandler->board,source);
    gameLogicHandler->board->pieces[source.x][source.y] = NULL;
    gameLogicHandler->board->pieces[destination.x][destination.y] = sourcePiece;
}
void promote(GameLogicHandler * gameLogicHandler, Square square) {
    getPiece(*gameLogicHandler->board, square)->isPromoted = true;
}


bool captureMove(GameLogicHandler * gameLogicHandler,  Square source ,Square destination){
    PieceColour turn = gameLogicHandler->turn;
    Piece * sourcePiece = getPiece(*gameLogicHandler->board,source);
    Piece * destinationPiece = getPiece(*gameLogicHandler->board,destination);
    if(!sourcePiece || destinationPiece || !isSquareOnTheBoard(destination) || turn != sourcePiece->colour) return false;

    int pieceRange = getPieceRange(*sourcePiece,false);
    int moveDistance = distanceBetweenSquares(source,destination);
    if(moveDistance>pieceRange) return false;

    MoveDirection moveDirection = getMoveDirection(source,destination,pieceRange);
    if (moveDirection==Failed) return false;

    Square squaresBetween[moveDistance-1];
    getSquaresBetween(gameLogicHandler,squaresBetween,source,destination,moveDirection);
    if(howManyPieces(*gameLogicHandler,squaresBetween,moveDistance)!=1)return false;

    Square capturedSquare = getFirstOccupiedSquare(*gameLogicHandler,squaresBetween);
    Piece * capturedPiece = getPiece(*gameLogicHandler->board,capturedSquare);
    if(capturedPiece->colour == sourcePiece->colour) return false;

    capture(gameLogicHandler,capturedSquare);
    makeMove(gameLogicHandler,source,destination);
    return true;

}
bool slideMove(GameLogicHandler * gameLogicHandler,  Square source ,Square destination){
    PieceColour turn = gameLogicHandler->turn;
    Piece * sourcePiece = getPiece(*gameLogicHandler->board,source);
    Piece * destinationPiece = getPiece(*gameLogicHandler->board,destination);
    if(!sourcePiece || destinationPiece || !isSquareOnTheBoard(destination) || turn != sourcePiece->colour) return false;

    int pieceRange = getPieceRange(*sourcePiece,true);
    int moveDistance = distanceBetweenSquares(source,destination);
    if(moveDistance>pieceRange)return false;

    MoveDirection moveDirection = getMoveDirection(source,destination,moveDistance);
    if (moveDirection==Failed || (!isMoveForward(moveDirection,sourcePiece->colour) && !sourcePiece->isSelected) ) return false;

    Square squaresBetween[moveDistance-1];
    getSquaresBetween(gameLogicHandler,squaresBetween,source,destination,moveDirection);
    int piecesBetween = howManyPieces(*gameLogicHandler,squaresBetween,moveDistance);
    if(piecesBetween)return false;

    makeMove(gameLogicHandler,source,destination);
    return true;


}

int getMaxCapture(GameLogicHandler gameLogicHandler){
    int result =0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Square currentSquare = (Square){i,j};
            Piece * currentPiece = getPiece(*gameLogicHandler.board,currentSquare);
            if(!currentPiece || currentPiece->colour!= gameLogicHandler.turn) continue;
            getMaxCaptureUtil(gameLogicHandler,*gameLogicHandler.board,&result,0,currentSquare);

        }
    }

    return result;
}

void getMaxCaptureUtil(GameLogicHandler  gameLogicHandler,Board board,int * result,int depth,Square square){
    *result = depth> *result ? depth : *result;

    Square everyDirection[4]={getSquareFromMoveDirection(TopLeft), getSquareFromMoveDirection(TopRight),
                              getSquareFromMoveDirection(DownLeft), getSquareFromMoveDirection(DownRight)};
    Piece * currentPiece = getPiece(board,square);
    if(!currentPiece) return;

    for (int i = 2; i <= getPieceRange(*currentPiece,false); ++i) {
        for (int j = 0; j < 4; ++j) {
            Board copiedBoard = copyBoard(board);
            Square nextSquare = plusSquare(square, multiplySquare(everyDirection[j],i));
            PieceColour currentTurn = gameLogicHandler.turn;
            GameLogicHandler nextGameLogicHandler;
            initializeGameLogicHandler(&nextGameLogicHandler,&copiedBoard,currentTurn);

            if(captureMove(&nextGameLogicHandler,square,nextSquare))
                getMaxCaptureUtil(gameLogicHandler,copiedBoard,result,depth+1, nextSquare);
        }
    }

}