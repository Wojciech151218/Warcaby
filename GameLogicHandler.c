
#include "GameLogicHandler.h"

void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board, PieceColour turn) {
	gameLogicHandler->board = board;
    gameLogicHandler->turn = turn;
    gameLogicHandler->capturedSquaresCount = 0;
    gameLogicHandler->pieceCapturing = NULL;
}
void copyCapturedSquaresAndCount(GameLogicHandler * gameLogicHandler,Square squares[],int count){
    for (int i = 0; i < count; ++i) {
        gameLogicHandler->capturedSquares[i] = squares[i];
    }
    gameLogicHandler->capturedSquaresCount = count;
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


bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler * moveHandler) {
    if(!moveHandler->isFinished) return false;

    int maxCaptureCount = getGlobalMaxCapture(*gameLogicHandler);
    int preMoveCaptureCount = getMaxCapture(*gameLogicHandler,moveHandler->source);

    if(gameLogicHandler->pieceCapturing){
        maxCaptureCount = preMoveCaptureCount;
        if(getPiece(*gameLogicHandler->board,moveHandler->source) != gameLogicHandler->pieceCapturing) {
            deselect(moveHandler);
            return false;
        }
    }
    if(!maxCaptureCount){// jesli nie ma bic
        if(slideMove(gameLogicHandler,moveHandler->source,moveHandler->destination)) return true;
        deselect(moveHandler);
        return false;
    }

    if(maxCaptureCount != preMoveCaptureCount) {
        deselect(moveHandler);
        return false;
    }

    GameLogicHandler * moveTester = malloc( sizeof(GameLogicHandler)) ;
    Board copiedBoard = copyBoard(*gameLogicHandler->board);
    initializeGameLogicHandler(moveTester,&copiedBoard,gameLogicHandler->turn);
    copyCapturedSquaresAndCount(moveTester,gameLogicHandler->capturedSquares,gameLogicHandler->capturedSquaresCount);

    if(!captureMove(moveTester,moveHandler->source,moveHandler->destination)){
        free(moveTester);
        deselect(moveHandler);
        return false;
    }
    int postMoveCaptureCount = getMaxCapture(*moveTester,moveHandler->destination);
    free(moveTester);

    if(postMoveCaptureCount+1 == preMoveCaptureCount){//jesli wybierzemy najsilniejsze bicie
        gameLogicHandler->pieceCapturing = getPiece(*gameLogicHandler->board,moveHandler->source);

        if(postMoveCaptureCount) {
            captureMove(gameLogicHandler, moveHandler->source, moveHandler->destination);
            updateAfterCapture(moveHandler, moveHandler->destination);
            return false;
        }
        captureMove(gameLogicHandler, moveHandler->source, moveHandler->destination);
        return true;

    }
    return false; //jesli wybierzemy słabsze bicie;
}
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler * moveHandler) {
    if(isSquarePromotable(gameLogicHandler,moveHandler->destination))
        promote(gameLogicHandler,moveHandler->destination);
    gameLogicHandler->pieceCapturing = NULL;
    gameLogicHandler->turn = !gameLogicHandler->turn;
    deselect(moveHandler);
    capture(gameLogicHandler);
    gameLogicHandler->capturedSquaresCount = 0;

}
bool isMoveForward(MoveDirection moveDirection, Piece * piece){
    if(piece->isPromoted) return  true;
    bool forwardForBlack = (moveDirection == TopRight || moveDirection == TopLeft) && piece->colour == Black;
    bool forwardForWhite = (moveDirection == DownRight || moveDirection == DownLeft) && piece->colour == White;
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
void capture(GameLogicHandler *gameLogicHandler) {
    for (int i = 0; i < gameLogicHandler->capturedSquaresCount; ++i) {
        Square square = gameLogicHandler->capturedSquares[i];
        gameLogicHandler->board->pieces[square.x][square.y] = NULL;
    }
}
void addSquareToCapture(GameLogicHandler * gameLogicHandler,Square square){
    gameLogicHandler->capturedSquares[gameLogicHandler->capturedSquaresCount++] = square;
}
bool isSquaredAlreadyCaptured(GameLogicHandler *gameLogicHandler, Square square){
    for (int i = 0; i < gameLogicHandler->capturedSquaresCount; ++i)
        if(equalSquare(gameLogicHandler->capturedSquares[i],square)) return true;
    return false;
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

    MoveDirection moveDirection = getMoveDirection(source,destination,moveDistance);
    if (moveDirection==Failed) return false;

    Square squaresBetween[moveDistance-1];
    getSquaresBetween(gameLogicHandler,squaresBetween,source,destination,moveDirection);
    if(howManyPieces(*gameLogicHandler,squaresBetween,moveDistance)!=1)return false;

    Square capturedSquare = getFirstOccupiedSquare(*gameLogicHandler,squaresBetween);
    Piece * capturedPiece = getPiece(*gameLogicHandler->board,capturedSquare);

    if(capturedPiece->colour == sourcePiece->colour ||
    isSquaredAlreadyCaptured(gameLogicHandler,capturedSquare)) return false;



    makeMove(gameLogicHandler,source,destination);
    addSquareToCapture(gameLogicHandler,capturedSquare);
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
    if (moveDirection==Failed || !isMoveForward(moveDirection,sourcePiece)) return false;

    Square squaresBetween[moveDistance-1];
    getSquaresBetween(gameLogicHandler,squaresBetween,source,destination,moveDirection);
    int piecesBetween = howManyPieces(*gameLogicHandler,squaresBetween,moveDistance);
    if(piecesBetween)return false;

    makeMove(gameLogicHandler,source,destination);
    return true;


}
int getMaxCapture(GameLogicHandler gameLogicHandler,Square pieceSquare){
    int result =0;
    getMaxCaptureUtil(&gameLogicHandler, &result, 0, pieceSquare);
    return result;
}

int getGlobalMaxCapture(GameLogicHandler gameLogicHandler) {
    int result =0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Square currentSquare = (Square){i,j};
            Piece * currentPiece = getPiece(*gameLogicHandler.board,currentSquare);
            if(!currentPiece || currentPiece->colour!= gameLogicHandler.turn) continue;
            getMaxCaptureUtil(&gameLogicHandler, &result, 0, currentSquare);

        }
    }

    return result;
}


void getMaxCaptureUtil(GameLogicHandler *gameLogicHandler, int *result, int depth, Square square) {
    *result = depth> *result ? depth : *result;

    Square everyDirection[4]={getSquareFromMoveDirection(TopLeft), getSquareFromMoveDirection(TopRight),
                              getSquareFromMoveDirection(DownLeft), getSquareFromMoveDirection(DownRight)};
    Piece * currentPiece = getPiece(*gameLogicHandler->board,square);
    //if(!currentPiece) return;

    for (int i = 2; i <= getPieceRange(*currentPiece,false); ++i) {
        for (int j = 0; j < 4; ++j) {
            Board copiedBoard = copyBoard(*gameLogicHandler->board);
            Square nextSquare = plusSquare(square, multiplySquare(everyDirection[j],i));
            PieceColour currentTurn = gameLogicHandler->turn;
            GameLogicHandler nextGameLogicHandler;
            initializeGameLogicHandler(&nextGameLogicHandler,&copiedBoard,currentTurn);
            copyCapturedSquaresAndCount(&nextGameLogicHandler,gameLogicHandler->capturedSquares,gameLogicHandler->capturedSquaresCount);

            if(captureMove(&nextGameLogicHandler,square,nextSquare))
                getMaxCaptureUtil(&nextGameLogicHandler, result, depth + 1, nextSquare);
        }
    }

}