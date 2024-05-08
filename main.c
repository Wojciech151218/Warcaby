#include <SFML/Window.h>
#include <SFML/Graphics.h>


int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfEvent event;

    // Create the main window
    window = sfRenderWindow_create(mode, "CSFML window", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    while (sfRenderWindow_isOpen(window))
    {
        // Process events
        while (sfRenderWindow_pollEvent(window, &event))
        {
            // Close window: exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        // Clear screen
        sfRenderWindow_clear(window, sfBlack);

        // Update the window
        sfRenderWindow_display(window);
    }

    // Cleanup resources
    sfRenderWindow_destroy(window);
    return 0;
}
