#include "Displayer.h"

Displayer getDisplayer(Board *board, sfRenderWindow *window){
    Displayer result;
    result.board = board;
    result.window = window;
    return result;
}

void display(Displayer * displayer) {
    sfCircleShape* circles[BOARD_SIZE * BOARD_SIZE];
    sfRectangleShape* squares[BOARD_SIZE * BOARD_SIZE];


    int circlesIndex = 0;
    int squaresIndex = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            squares[squaresIndex] = sfRectangleShape_create();
            setSquare(squares[squaresIndex++],(i+j)%2 ,i ,j);

            if (!displayer->board->pieces[i][j]) {
                circles[circlesIndex++] = NULL;
                continue;
            }
            circles[circlesIndex] = sfCircleShape_create();
            Piece * currentPiece = displayer->board->pieces[i][j];
            if(currentPiece->isSelected)
                setSelectedPiece(circles[circlesIndex++],currentPiece->colour,i,j);
            else
                setPiece(circles[circlesIndex++],currentPiece->colour,i,j);
            if(currentPiece->isPromoted)
                setPromotedPiece(circles[circlesIndex-1],currentPiece->colour,i,j);
        }
    }
    // Clear the window
    sfRenderWindow_clear(displayer->window, hex_to_sfColor(DARK_TILE_COLOUR));

    // Draw the circle
    for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (squares[i]) sfRenderWindow_drawRectangleShape(displayer->window, squares[i], NULL);
        if (circles[i] ) sfRenderWindow_drawCircleShape(displayer->window, circles[i], NULL);

    }

    // Display the window
    sfRenderWindow_display(displayer->window);

    for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (squares[i] ) sfRectangleShape_destroy(squares[i]);
        if (circles[i]) sfCircleShape_destroy(circles[i]);
    }

}
void setSelectedPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j){
    sfCircleShape_setRadius(circleShape, WINDOW_SIZE / BOARD_SIZE / 2);
    sfCircleShape_setPosition(circleShape, (sfVector2f) { i* WINDOW_SIZE / BOARD_SIZE, j* WINDOW_SIZE / BOARD_SIZE });
    if (pieceColour == Black)
        sfCircleShape_setFillColor(circleShape,hex_to_sfColor("#000fff") );
    else
        sfCircleShape_setFillColor(circleShape,hex_to_sfColor("#fff000") );

}
void setPromotedPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j){
    sfCircleShape_setRadius(circleShape, WINDOW_SIZE / BOARD_SIZE / 2);
    sfCircleShape_setPosition(circleShape, (sfVector2f) { i* WINDOW_SIZE / BOARD_SIZE, j* WINDOW_SIZE / BOARD_SIZE });
    sfCircleShape_setOutlineThickness(circleShape,2.0f);

    if (pieceColour == Black) {
        sfCircleShape_setFillColor(circleShape, hex_to_sfColor(DARK_PIECE_COLOUR));
        sfCircleShape_setOutlineColor(circleShape,hex_to_sfColor(LIGHT_PIECE_COLOUR));
    }
    else {
        sfCircleShape_setFillColor(circleShape, hex_to_sfColor(LIGHT_PIECE_COLOUR));
        sfCircleShape_setOutlineColor(circleShape,hex_to_sfColor(DARK_PIECE_COLOUR));
    }
}
void setPiece(sfCircleShape *  circleShape,PieceColour pieceColour,int i,int j){
    sfCircleShape_setRadius(circleShape, WINDOW_SIZE / BOARD_SIZE / 2);
    sfCircleShape_setPosition(circleShape, (sfVector2f) { i* WINDOW_SIZE / BOARD_SIZE, j* WINDOW_SIZE / BOARD_SIZE });
    if (pieceColour == Black)
        sfCircleShape_setFillColor(circleShape,hex_to_sfColor(DARK_PIECE_COLOUR) );
    else
        sfCircleShape_setFillColor(circleShape,hex_to_sfColor(LIGHT_PIECE_COLOUR) );
}
void setSquare(sfRectangleShape *  rectangleShape,PieceColour pieceColour,int i,int j){
    sfVector2f size = { WINDOW_SIZE / BOARD_SIZE, WINDOW_SIZE / BOARD_SIZE };
    sfRectangleShape_setSize(rectangleShape, size);
    sfVector2f position = { i * WINDOW_SIZE / BOARD_SIZE, j * WINDOW_SIZE / BOARD_SIZE };
    sfRectangleShape_setPosition(rectangleShape, position);
    sfColor color = pieceColour ? hex_to_sfColor(LIGHT_TILE_COLOUR) : hex_to_sfColor(DARK_TILE_COLOUR);
    sfRectangleShape_setFillColor(rectangleShape, color);

}