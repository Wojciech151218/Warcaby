#include "MoveHandler.h"
bool equalMove(Move a, Move b) {
    return a.x == b.x && a.y == b.y;
}


 Move getCurrentMove(sfRenderWindow* window, sfEvent * event) {
    // Check if right click is pressed
    
    if (event->type == sfEvtMouseButtonReleased ){

        sfVector2i mousePosition = sfMouse_getPositionRenderWindow(window);
        float cellSize =(float)WINDOW_SIZE/ BOARD_SIZE ;

        // Convert mouse position to board coordinates
        int boardX =  mousePosition.x / cellSize;
        int boardY = mousePosition.y / cellSize;
        // Ensure the coordinates are within the board bounds
        if (boardX >= 0 && boardX < BOARD_SIZE && boardY >= 0 && boardY < BOARD_SIZE) {
            Move move;
            move.x = boardX;
            move.y = boardY;
            
            return move;
        }
        else {
            // Return an invalid move if outside board bounds
            Move invalidMove = { -1, -1 };
            return invalidMove;
        }
    }
    else {
        // Return an invalid move if right click is not pressed
        Move invalidMove = { -1, -1 };
        return invalidMove;
    }
}

 void deselect(MoveHandler * moveHandler) {
     moveHandler->isSelected = false;
     moveHandler->isDone = false;
     moveHandler->source = (Move){ -1, -1 };
     moveHandler->destination = (Move){ -1, -1 };
 }
 void initializeMoveHandler(MoveHandler* moveHandler, sfEvent * event) {
     moveHandler->event = event;
     deselect(moveHandler);
 }

void handleMove(MoveHandler* moveHandler,sfRenderWindow * window) {//TODO mega sraka
   
    if (!moveHandler->isSelected) {
        Move source = getCurrentMove(window,moveHandler->event);

        if (source.x == -1) return;
        moveHandler->source = source;
        moveHandler->isSelected = false;
    }

}