#include <SFML/Graphics.h>
#include "Displayer.h"
#include "Auxilary.h"
#include "GameLogicHandler.h"
#include "GameStateHandler.h"
void initializeGame(sfRenderWindow* window,sfEvent * event, Displayer * displayer,Board * board,MoveHandler * moveHandler,GameLogicHandler * gameLogicHandler){
    *displayer = getDisplayer(board, window);
    initializeMoveHandler(moveHandler,event);
    initializeGameLogicHandler(gameLogicHandler,board,White);
}

int main()
{
    sfVideoMode mode = { WINDOW_SIZE, WINDOW_SIZE, 64 };
    sfRenderWindow* window;
    window = sfRenderWindow_create(mode, "Warcaby", sfResize | sfClose, NULL);
    sfEvent event;
    Board * board = getStarterBoard();

    Displayer displayer;
    MoveHandler moveHandler;
    GameLogicHandler gameLogicHandler;
    GameStateHandler gameStateHandler;

    initializeGame(window,&event,&displayer,board,&moveHandler,&gameLogicHandler);
    initializeGameStateHandler(&gameStateHandler,board,White);
    if(!isGameDirectoryEmpty(&gameStateHandler)){
        PieceColour turn = readTurnFromTheFile(gameStateHandler);
        readBoardFromFile(&gameStateHandler, board);
        gameLogicHandler.turn = turn;
        saveGame(&gameStateHandler, White);
    }


    // Create the main window
    if (!window)
        return 1;

    // Create a circle

    // Start the game loop
    while (sfRenderWindow_isOpen(window))
    {
        // Process events
        while (sfRenderWindow_pollEvent(window, &event)){
            // Close window: exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        if (sfKeyboard_isKeyPressed(sfKeyN)) {
            resetBoardFile(&gameStateHandler);
            initializeGame(window,&event,&displayer,board,&moveHandler,&gameLogicHandler);
            initializeGameStateHandler(&gameStateHandler,board,White);
        }


        handleMove(&moveHandler, window, *board, gameLogicHandler.turn);
        display(&displayer);
        if (isMoveLegal(&gameLogicHandler,&moveHandler)) {
            executeMove(&gameLogicHandler, &moveHandler);
            saveGame(&gameStateHandler, gameLogicHandler.turn);
        }
    }
    sfRenderWindow_destroy(window);

    return 0;
}
