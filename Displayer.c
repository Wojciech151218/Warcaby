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
    sfSprite* sprite = sfSprite_create();
    sfRectangleShape* square = sfRectangleShape_create();

    sfTexture* promotedWhiteTexture = displayer->promotedWhiteTexture;
    sfTexture* promotedBlackTexture = displayer->promotedBlackTexture;
    sfTexture* whiteTexture = displayer->whiteTexture;
    sfTexture* blackTexture = displayer->blackTexture;

    sfRenderWindow_clear(displayer->window, hex_to_sfColor(DARK_TILE_COLOUR));
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            setSquare(square,(i+j)%2 ,i ,j);
            sfRenderWindow_drawRectangleShape(displayer->window, square, NULL);

            if (!displayer->board->pieces[i][j]) continue;

            Piece * currentPiece = displayer->board->pieces[i][j];
            if(currentPiece->isSelected)
                setSelectedPiece(sprite,currentPiece->colour);
            else
                sfSprite_setColor(sprite,sfWhite);
            if(currentPiece->isPromoted)
                setSpriteTexture(sprite, currentPiece->colour==White?promotedWhiteTexture:promotedBlackTexture, i, j);
            else
                setSpriteTexture(sprite, currentPiece->colour == White ? whiteTexture : blackTexture, i,j);


            sfRenderWindow_drawSprite(displayer->window, sprite ,NULL);
        }
    }
    sfRenderWindow_display(displayer->window);

    sfRectangleShape_destroy(square);
    sfSprite_destroy(sprite);

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