#include "MoveHandler.h"




 Square getCurrentSquare(sfRenderWindow* window, sfEvent * event) {


     sfVector2i mousePosition = sfMouse_getPositionRenderWindow(window);
     float cellSize = (float) WINDOW_SIZE / BOARD_SIZE;

     // Convert mouse position to board coordinates
     int boardX = mousePosition.x / cellSize;
     int boardY = mousePosition.y / cellSize;
     // Ensure the coordinates are within the board bounds
     if (boardX >= 0 && boardX < BOARD_SIZE && boardY >= 0 && boardY < BOARD_SIZE) {
         Square move;
         move.x = boardX;
         move.y = boardY;

         return move;
     } else {
         // Return an invalid move if outside board bounds
         Square invalidMove = {-1, -1};
         return invalidMove;
     }

 }
 void deselect(MoveHandler * moveHandler) {
     if(moveHandler->pieceSelected)
         moveHandler->pieceSelected->isSelected = false;
     moveHandler->pieceSelected = NULL;
     moveHandler->isFinished = false;
     moveHandler->source = (Square){-1, -1 };
     moveHandler->destination = (Square){-1, -1 };

 }
void updateAfterCapture(MoveHandler *moveHandler, Square newSource) {
    moveHandler->isFinished = false;
    moveHandler->source = newSource;
    moveHandler->destination = (Square){-1, -1 };
}

void initializeMoveHandler(MoveHandler* moveHandler, sfEvent * event) {
     moveHandler->event = event;
     moveHandler->pieceSelected = NULL;
     moveHandler->isFinished = false;
     moveHandler->source = (Square){-1, -1 };
     moveHandler->destination = (Square){-1, -1 };
 }

void handleMove(MoveHandler *moveHandler, sfRenderWindow *window, Board board, PieceColour turn) {
    if(moveHandler->event->type != sfEvtMouseButtonPressed ) return;

    Square square = getCurrentSquare(window, moveHandler->event);
    if(square.x ==-1) return;

    Piece * piece = getPiece(board, square);
    if(moveHandler->pieceSelected == piece) return;
    if(piece && piece->colour!=turn) return;


    if(!moveHandler->pieceSelected){
        moveHandler->source = square;
        moveHandler->pieceSelected = piece;

        piece->isSelected = true;

    }else{
        moveHandler->destination= square;
        moveHandler->isFinished = true;
    }


}
Piece * getPiece(Board board, Square square){
    if(!isSquareOnTheBoard(square)) return NULL;
    return board.pieces[square.x][square.y];
}