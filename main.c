#include <SFML/Graphics.h>
#include "Displayer.h"
#include "Auxilary.h"
#include "GameLogicHandler.h"
#include "GameFileHandler.h"
void initializeGame(sfRenderWindow* window,sfEvent * event, Displayer * displayer,Board * board,MoveHandler * moveHandler,GameLogicHandler * gameLogicHandler){
    *displayer = getDisplayer(board, window);
    initializeMoveHandler(moveHandler,event);
    initializeGameLogicHandler(gameLogicHandler,board,White);
}
void resetGame(GameFileHandler * gameFileHandler,Board ** board,GameLogicHandler * gameLogicHandler,Displayer * displayer){
    resetBoardFile(gameFileHandler);
    deleteBoard(*board);
    *board = getStarterBoard();
    gameLogicHandler->board = *board;
    gameLogicHandler->turn = White;
    gameFileHandler->board = *board;
    displayer->board = *board;
    saveGame(gameFileHandler,White);
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
    GameFileHandler gameFileHandler;

    initializeGame(window,&event,&displayer,board,&moveHandler,&gameLogicHandler);
    initializeGameFileHandler(&gameFileHandler, board, White);
    if(!isGameDirectoryEmpty(&gameFileHandler)){
        PieceColour turn = readTurnFromTheFile(gameFileHandler);
        readBoardFromFile(&gameFileHandler, board);
        gameLogicHandler.turn = turn;
        saveGame(&gameFileHandler, White);
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
        if (sfKeyboard_isKeyPressed(sfKeyN))
            resetGame(&gameFileHandler,&board,&gameLogicHandler,&displayer);


        handleMove(&moveHandler, window, *board, gameLogicHandler.turn);
        display(&displayer);
        if (isMoveLegal(&gameLogicHandler,&moveHandler)) {
            executeMove(&gameLogicHandler, &moveHandler);
            saveGame(&gameFileHandler, gameLogicHandler.turn);
        }
        if(getGameState(*board)!=InGame)
            resetGame(&gameFileHandler,&board,&gameLogicHandler,&displayer);

    }
    sfRenderWindow_destroy(window);

    return 0;
}
