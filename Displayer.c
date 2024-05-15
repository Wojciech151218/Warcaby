#include "SFML/Graphics.h"
#include "Displayer.h"

Displayer getDisplayer(Board *board, sfRenderWindow *window) {
    Displayer result;
    result.board = board;
    result.window = window;
    return result;
}

void display(Displayer *displayer) {
    sfSprite* sprites[BOARD_SIZE * BOARD_SIZE];
    sfRectangleShape* squares[BOARD_SIZE * BOARD_SIZE];

    sfTexture* whiteTexture = sfTexture_createFromFile("sprites/white.png", NULL);
    sfTexture* blackTexture = sfTexture_createFromFile("sprites/black.png", NULL);
    sfTexture* promotedWhiteTexture = sfTexture_createFromFile("sprites/promoted/damka_biala.png", NULL);
    sfTexture* promotedBlackTexture = sfTexture_createFromFile("sprites/promoted/damka_czarna.png", NULL);

    int spriteIndex = 0;
    int squaresIndex = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            squares[squaresIndex] = sfRectangleShape_create();
            sfVector2f size = { WINDOW_SIZE / BOARD_SIZE, WINDOW_SIZE / BOARD_SIZE };
            sfRectangleShape_setSize(squares[squaresIndex], size);
            sfVector2f position = { i * WINDOW_SIZE / BOARD_SIZE, j * WINDOW_SIZE / BOARD_SIZE };
            sfRectangleShape_setPosition(squares[squaresIndex], position);

            sfColor color = (i + j) % 2 ? hex_to_sfColor(LIGHT_TILE_COLOUR) : hex_to_sfColor(DARK_TILE_COLOUR);
            sfRectangleShape_setFillColor(squares[squaresIndex++], color);

            Piece * currentPiece = displayer->board->pieces[i][j];

            if (!currentPiece) {
                sprites[spriteIndex++] = NULL;
                continue;
            }
            sprites[spriteIndex] = sfSprite_create();
            sfSprite_setScale(sprites[spriteIndex], (sfVector2f){0.025,0.025});
            sfVector2f squarePosition = { i * WINDOW_SIZE / BOARD_SIZE, j * WINDOW_SIZE / BOARD_SIZE };
            sfVector2f spritePosition = {
                    squarePosition.x + (WINDOW_SIZE / BOARD_SIZE - 0.7 * WINDOW_SIZE / BOARD_SIZE) / 2,
                    squarePosition.y + (WINDOW_SIZE / BOARD_SIZE - 0.75 * WINDOW_SIZE / BOARD_SIZE) / 2
            };
            sfSprite_setPosition(sprites[spriteIndex], spritePosition);

            if (currentPiece->isPromoted) {
                if (currentPiece->colour == Black) {
                    sfSprite_setTexture(sprites[spriteIndex], promotedBlackTexture, sfTrue);
                } else {
                    sfSprite_setTexture(sprites[spriteIndex], promotedWhiteTexture, sfTrue);
                }
            }else{
                if (currentPiece->colour == Black){
                    sfSprite_setTexture(sprites[spriteIndex], blackTexture, sfTrue);
                } else {
                    sfSprite_setTexture(sprites[spriteIndex], whiteTexture, sfTrue);
                }
            }
            spriteIndex++;
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
        if (squares[i]) sfRectangleShape_destroy(squares[i]);
        if (sprites[i]) sfSprite_destroy(sprites[i]);
    }
    sfTexture_destroy(whiteTexture);
    sfTexture_destroy(blackTexture);
}