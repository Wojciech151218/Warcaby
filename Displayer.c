#include "Displayer.h"

Displayer getDisplayer(Board *board, sfRenderWindow *window){
    Displayer result;
    result.board = board;
    result.window = window;
    result.promotedWhiteTexture = sfTexture_createFromFile("sprites/promoted/damka_biala.png", NULL);
    result.promotedBlackTexture = sfTexture_createFromFile("sprites/promoted/damka_czarna.png", NULL);
    result.whiteTexture = sfTexture_createFromFile("sprites/white.png", NULL);
    result.blackTexture = sfTexture_createFromFile("sprites/black.png", NULL);
    return result;
}

void display(Displayer * displayer) {
    sfSprite* sprites[BOARD_SIZE * BOARD_SIZE];
    sfRectangleShape* squares[BOARD_SIZE * BOARD_SIZE];

    sfTexture* promotedWhiteTexture = displayer->promotedWhiteTexture;
    sfTexture* promotedBlackTexture = displayer->promotedBlackTexture;
    sfTexture* whiteTexture = displayer->whiteTexture;
    sfTexture* blackTexture = displayer->blackTexture;

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
            if(currentPiece->isPromoted)
                setSpriteTexture(sprites[spritesIndex], currentPiece->colour==White?promotedWhiteTexture:promotedBlackTexture, i, j);
            else
                setSpriteTexture(sprites[spritesIndex], currentPiece->colour == White ? whiteTexture : blackTexture, i,j);
            if(currentPiece->isSelected)
                setSelectedPiece(sprites[spritesIndex],currentPiece->colour);
            spritesIndex++;
        }
    }
    // Clear the window
    sfRenderWindow_clear(displayer->window, hex_to_sfColor(DARK_TILE_COLOUR));

    // Draw the circle
    for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (squares[i]) sfRenderWindow_drawRectangleShape(displayer->window, squares[i], NULL);
        if (sprites[i]) sfRenderWindow_drawSprite(displayer->window, sprites[i], NULL);

    }

    // Display the window
    sfRenderWindow_display(displayer->window);

    for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (squares[i]) sfRectangleShape_destroy(squares[i]);
        if (sprites[i]) sfSprite_destroy(sprites[i]);
    }
}
void setSelectedPiece(sfSprite *sprite, PieceColour colour) {
   if(colour == White)
        sfSprite_setColor(sprite, sfColor_fromRGB(128, 128, 128));
   else
       sfSprite_setColor(sprite, sfColor_fromRGB(128, 128, 128));
}

void setSpriteTexture(sfSprite *sprite, sfTexture *texture, int i, int j) {
    sfSprite_setScale(sprite, (sfVector2f){0.025f,0.025f});
    sfSprite_setPosition(sprite, (sfVector2f) {
        (i *(float) WINDOW_SIZE / BOARD_SIZE) + ((float) WINDOW_SIZE / BOARD_SIZE - 0.7f * WINDOW_SIZE / BOARD_SIZE) / 2,
        (j * (float)WINDOW_SIZE / BOARD_SIZE) +  ((float) WINDOW_SIZE / BOARD_SIZE - 0.75f * WINDOW_SIZE / BOARD_SIZE) / 2
    });
    sfSprite_setTexture(sprite, texture,sfTrue);

}
void setSquare(sfRectangleShape *  rectangleShape,PieceColour pieceColour,int i,int j){
    sfVector2f size = { (float)WINDOW_SIZE / BOARD_SIZE, (float)WINDOW_SIZE / BOARD_SIZE };
    sfRectangleShape_setSize(rectangleShape, size);
    sfVector2f position = { i * (float)WINDOW_SIZE / BOARD_SIZE, j * (float)WINDOW_SIZE / BOARD_SIZE };
    sfRectangleShape_setPosition(rectangleShape, position);
    sfColor color = pieceColour ? hex_to_sfColor(LIGHT_TILE_COLOUR) : hex_to_sfColor(DARK_TILE_COLOUR);
    sfRectangleShape_setFillColor(rectangleShape, color);
}