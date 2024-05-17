#include "Auxilary.h"
#include "MoveHandler.h"
#include "Board.h"

struct GameLogicHandler {
	Board * board;
    PieceColour turn;
    Square capturedSquares[];
} typedef GameLogicHandler;
enum MoveDirection{
    TopRight,
    TopLeft,
    DownRight,
    DownLeft,
    Failed

}typedef MoveDirection;


void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board, PieceColour turn);
GameLogicHandler copyGameLogicHandler(GameLogicHandler gameLogicHandler);
void deleteGameLogicHandler(GameLogicHandler * gameLogicHandler);

void capture(GameLogicHandler * gameLogicHandler, Square square);
void makeMove(GameLogicHandler * gameLogicHandler,Square source, Square destination);
void promote(GameLogicHandler * gameLogicHandler, Square square);

MoveDirection getMoveDirection(Square source , Square destination, int moveDistance);
Square getSquareFromMoveDirection(MoveDirection moveDirection);
Square getFirstOccupiedSquare(GameLogicHandler gameLogicHandler,Square squares[]);

bool isMoveForward(MoveDirection moveDirection, Piece *piece);
bool isSquarePromotable(GameLogicHandler * gameLogicHandler,Square square);
int getPieceRange(Piece piece,bool slide);

bool captureMove(GameLogicHandler * gameLogicHandler, Square source ,Square destination);
bool slideMove(GameLogicHandler * gameLogicHandler, Square source ,Square destination);

void getSquaresBetween(GameLogicHandler * gameLogicHandler, Square  squares[],Square  source , Square destination,MoveDirection moveDirection);
int howManyPieces(GameLogicHandler gameLogicHandler, Square  squares[],int moveDistance);

bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler * moveHandler);
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler * moveHandler);

//Algorytm szukania maksymalenej liczby zbic
int getMaxCapture(GameLogicHandler gameLogicHandler, Piece *piece);
void getMaxCaptureUtil(GameLogicHandler  gameLogicHandler,Board board,int * result,int depth,Square square);