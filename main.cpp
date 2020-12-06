#include "DeepSpaceDodge.h"

/**
 * Entry point to the application.
 * Create a new game, load in high scores, then show menu
 * 
 * @returns status code of program exit
 */
int main() {
    Game *game = new Game();
    game->loadHighScores();
    game->showMenuScreen();
    delete game;

    return 0;
}     