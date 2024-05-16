#include "Displayer.h"

Displayer getDisplayer(Board *board, sfRenderWindow *window){
    Displayer result;
    result.board = board;
    result.window = window;
    return result;
}

void display(Displayer * displayer) {
    sfSprite* sprites[BOARD_SIZE * BOARD_SIZE];
    sfRectangleShape* squares[BOARD_SIZE * BOARD_SIZE];

    int spritesIndex = 0;
    int squaresIndex = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            squares[squaresIndex] = sfRectangleShape_create();
            setSquare(squares[squaresIndex++],(i+j)%2 ,i ,j);

            if (!displayer->board->pieces[i][j]) {
                sprites[spritesIndex++] = NULL;
                continue;
            }
            sprites[spritesIndex] = sfSprite_create();
            Piece * currentPiece = displayer->board->pieces[i][j];
            if(currentPiece->isSelected)
                setSelectedPiece(sprites[spritesIndex], currentPiece->colour, i, j);
            else
                setPiece(sprites[spritesIndex], currentPiece->colour, i, j);
            if(currentPiece->isPromoted)
                setPromotedPiece(sprites[spritesIndex], currentPiece->colour, i, j);
            spritesIndex++;
        }
    }
    // Clear the window
    sfRenderWindow_clear(displayer->window, hex_to_sfColor(DARK_TILE_COLOUR));

    // Draw the circle
    for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (squares[i]) sfRenderWindow_drawRectangleShape(displayer->window, squares[i], NULL);
        if (sprites[i] ) sfRenderWindow_drawSprite(displayer->window, sprites[i], NULL);

    }

    // Display the window
    sfRenderWindow_display(displayer->window);

    for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (squares[i] ) sfRectangleShape_destroy(squares[i]);
        if (sprites[i]) sfSprite_destroy(sprites[i]);
    }
}
void setSelectedPiece(sfSprite *sprite, PieceColour pieceColour, int i, int j) {
    sfSprite_setScale(sprite, (sfVector2f){0.025,0.025});
    sfSprite_setPosition(sprite, (sfVector2f) {i * (float) WINDOW_SIZE / BOARD_SIZE, j * (float)WINDOW_SIZE / BOARD_SIZE });
    sfTexture* whiteTexture = sfTexture_createFromFile("sprites/white.png", NULL);
    sfTexture* blackTexture = sfTexture_createFromFile("sprites/black.png", NULL);
    if(pieceColour == White) {
        sfSprite_setTexture(sprite, whiteTexture, sfTrue);
        sfSprite_setColor(sprite, sfColor_fromRGB(0, 0, 255));
    } else {
        sfSprite_setTexture(sprite, blackTexture, sfTrue);
        sfSprite_setColor(sprite, sfColor_fromRGB(255, 255, 0));
    }
    sfTexture_destroy(blackTexture);
    sfTexture_destroy(whiteTexture);

}
void setPromotedPiece(sfSprite *sprite, PieceColour pieceColour, int i, int j) {
    sfSprite_setScale(sprite, (sfVector2f){0.025,0.025});
    sfSprite_setPosition(sprite, (sfVector2f) {i * (float) WINDOW_SIZE / BOARD_SIZE, j * (float)WINDOW_SIZE / BOARD_SIZE });
    sfTexture* promotedWhiteTexture = sfTexture_createFromFile("sprites/promoted/damka_biala.png", NULL);
    sfTexture* promotedBlackTexture = sfTexture_createFromFile("sprites/promoted/damka_czarna.png", NULL);
    if(pieceColour == White)
        sfSprite_setTexture(sprite, promotedWhiteTexture,sfTrue);
    else
        sfSprite_setTexture(sprite, promotedBlackTexture,sfTrue);

    sfTexture_destroy(promotedWhiteTexture);
    sfTexture_destroy(promotedBlackTexture);
}
void setPiece(sfSprite *sprite, PieceColour pieceColour, int i, int j) {
    sfSprite_setScale(sprite, (sfVector2f){0.025,0.025});
    sfSprite_setPosition(sprite, (sfVector2f) {i * (float) WINDOW_SIZE / BOARD_SIZE, j * (float)WINDOW_SIZE / BOARD_SIZE });
    sfTexture* whiteTexture = sfTexture_createFromFile("sprites/white.png", NULL);
    sfTexture* blackTexture = sfTexture_createFromFile("sprites/black.png", NULL);
    if(pieceColour == White)
        sfSprite_setTexture(sprite, whiteTexture,sfTrue);
    else
        sfSprite_setTexture(sprite, blackTexture,sfTrue);

    sfTexture_destroy(blackTexture);
    sfTexture_destroy(whiteTexture);
}
void setSquare(sfRectangleShape *  rectangleShape,PieceColour pieceColour,int i,int j){
    sfVector2f size = { (float)WINDOW_SIZE / BOARD_SIZE, (float)WINDOW_SIZE / BOARD_SIZE };
    sfRectangleShape_setSize(rectangleShape, size);
    sfVector2f position = { i * (float)WINDOW_SIZE / BOARD_SIZE, j * (float)WINDOW_SIZE / BOARD_SIZE };
    sfRectangleShape_setPosition(rectangleShape, position);
    sfColor color = pieceColour ? hex_to_sfColor(LIGHT_TILE_COLOUR) : hex_to_sfColor(DARK_TILE_COLOUR);
    sfRectangleShape_setFillColor(rectangleShape, color);

}