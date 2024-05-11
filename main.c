#include <SFML/Graphics.h>
#include "Displayer.h"
#include "Auxilary.h"
#include "GameLogicHandler.h"
int main()
{
    sfVideoMode mode = { WINDOW_SIZE, WINDOW_SIZE, 64 };
    sfRenderWindow* window;
    sfEvent event;
    Board * board = getStarterBoard();
    Displayer displayer = initialize(board);
    MoveHandler moveHandler;
    initializeMoveHandler(&moveHandler,&event);
    GameLogicHandler gameLogicHandler;
    initializeGameLogicHandler(&gameLogicHandler,board,White);

    // Create the main window
    window = sfRenderWindow_create(mode, "Warcaby", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    // Create a circle

    // Start the game loop
    while (sfRenderWindow_isOpen(window))
    {
        // Process events
        while (sfRenderWindow_pollEvent(window, &event))
        {
            // Close window: exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }



        handleMove(&moveHandler,window);
        display(displayer, window, moveHandler);
        if ( isMoveLegal(&gameLogicHandler, &moveHandler)) {
            executeMove(&gameLogicHandler, &moveHandler);

        }

    }


    sfRenderWindow_destroy(window);

    return 0;
}
