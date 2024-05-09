#include "Displayer.h"

Displayer initialize(Board * board) {
	Displayer result;
	result.board = board;
	return result;
}

void display(Displayer displayer, sfRenderWindow* window, MoveHandler moveHanlder) {
	sfCircleShape* circles[BOARD_SIZE * BOARD_SIZE];
	sfRectangleShape* squares[BOARD_SIZE * BOARD_SIZE];
	Square selectedToMove = moveHanlder.source;


	int circlesIndex = 0;
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

			if (!displayer.board->pieces[i][j]) {
				circles[circlesIndex++] = NULL;
				continue;
			}
			circles[circlesIndex] = sfCircleShape_create();
			sfCircleShape_setRadius(circles[circlesIndex], WINDOW_SIZE / BOARD_SIZE / 2);
			sfCircleShape_setPosition(circles[circlesIndex], (sfVector2f) { i* WINDOW_SIZE / BOARD_SIZE, j* WINDOW_SIZE / BOARD_SIZE });


			if (displayer.board->pieces[i][j]->colour == Black)
				sfCircleShape_setFillColor(circles[circlesIndex++], equalSquare(selectedToMove,(Square){i, j}) ?
					hex_to_sfColor("#000000") : hex_to_sfColor(DARK_PIECE_COLOUR) );
			else
				sfCircleShape_setFillColor(circles[circlesIndex++], equalSquare(selectedToMove, (Square) {i, j }) ?
					hex_to_sfColor("#000000") : hex_to_sfColor(LIGHT_PIECE_COLOUR) );


		}
	}
		// Clear the window
	sfRenderWindow_clear(window, sfGreen);

		// Draw the circle
	for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		if (squares[i]) sfRenderWindow_drawRectangleShape(window, squares[i], NULL);
		if (circles[i] ) sfRenderWindow_drawCircleShape(window, circles[i], NULL);
		
	}


	// Display the window
	sfRenderWindow_display(window);

	for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		if (squares[i] ) sfRectangleShape_destroy(squares[i]);
		if (circles[i]) sfCircleShape_destroy(circles[i]);
	}
	
}