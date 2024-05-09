#include "Auxilary.h"
#include "MoveHandler.h"
#include "Board.h"

struct GameLogicHandler {
	Board * board;
    PieceColour turn;
} typedef GameLogicHandler;
enum MoveDirection{
    TopRight,
    TopLeft,
    DownRight,
    DownLeft,
    Failed

}typedef MoveDirection;


void initializeGameLogicHandler(GameLogicHandler* gameLogicHandler, Board * board);
void makeMove(GameLogicHandler * gameLogicHandler,Square source, Square destination);
MoveDirection getMoveDirection(Square source , Square destination, int moveDistance);
Square getSquareFromMoveDirection(MoveDirection moveDirection);
Square getFirstOccupiedSquare(GameLogicHandler gameLogicHandler,Square squares[]);
bool isMoveForward(MoveDirection moveDirection,PieceColour pieceColour);

void captureMove(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler);
void slideMove(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler);

void capture(GameLogicHandler * gameLogicHandler, Square square);
void getSquaresBetween(GameLogicHandler * gameLogicHandler, Square  squares[],Square  source , Square destination,MoveDirection moveDirection);
int howManyPieces(GameLogicHandler gameLogicHandler, Square  squares[],int moveDistance);

bool isMoveLegal(GameLogicHandler * gameLogicHandler, MoveHandler moveHandler);
void executeMove(GameLogicHandler* gameLogicHandler, MoveHandler * moveHandler);