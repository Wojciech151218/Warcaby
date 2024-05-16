#pragma once
#include "Board.h"
#include "Auxilary.h"
#include "MoveHandler.h"

struct Displayer{
	Board * board;
    sfRenderWindow * window;
    sfTexture* promotedWhiteTexture;
    sfTexture* promotedBlackTexture;
    sfTexture* whiteTexture;
    sfTexture* blackTexture;

} typedef Displayer;

Displayer getDisplayer(Board *board, sfRenderWindow *window);
void display(Displayer *displayer);

void setSelectedPiece(sfSprite *sprite, PieceColour colour);

void setSpriteTexture(sfSprite *sprite, sfTexture *texture, int i, int j);
void setSquare(sfRectangleShape *  rectangleShape,PieceColour pieceColour,int i,int j);
