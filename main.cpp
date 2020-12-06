#include "DeepSpaceDodge.h"

/**
 * Entry into main program, loads high scores then shows the menu
 * Programmed by Robert Pafford
 */
int main() {
    Game *game = new Game();
    game->loadHighScores();
    game->showMenuScreen();
    delete game;

    return 0;
}