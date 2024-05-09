#include "MoveHandler.h"
bool equalSquare(Square a, Square b) {
    return a.x == b.x && a.y == b.y;
}


 Square getCurrentSquare(sfRenderWindow* window, sfEvent * event) {
     // Check if right click is pressed



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
     moveHandler->pieceSelected = NULL;
     moveHandler->isFinished = false;
     moveHandler->source = (Square){-1, -1 };
     moveHandler->destination = (Square){-1, -1 };

 }
 void initializeMoveHandler(MoveHandler* moveHandler, sfEvent * event) {
     moveHandler->event = event;
     deselect(moveHandler);
 }

void handleMove(MoveHandler* moveHandler,sfRenderWindow * window) {
    if(moveHandler->event->type != sfEvtMouseButtonReleased ) return;

    Square square = getCurrentSquare(window, moveHandler->event);
    if(square.x ==-1) return;

    Piece * piece = getPiece(*moveHandler->board, square);


    if(!moveHandler->pieceSelected && piece){
        moveHandler->source = square;
        moveHandler->pieceSelected = piece;
        return;
    }
    if(moveHandler->pieceSelected && moveHandler->pieceSelected != piece){
        moveHandler->destination= square;
        moveHandler->isFinished = true;
    }


}
Piece * getPiece(Board board, Square square){
    return board.pieces[square.x][square.y];
}