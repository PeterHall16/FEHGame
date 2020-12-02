#include "FEHLCD.h"
#include "DeepSpaceDodge.h"

/**
 * Entry point to the application.
 * 
 * @returns status code of program exit
 */
int main() {
    Game *game = new Game();
    game->showMenuScreen();
    delete game;

    return 0;
}

/**
 * Displays menu screen.
 */
void Game::showMenuScreen() {
    LCD.Clear();

    // Define variables
    int width = 190;
    int height = 35;
    int buttonX = 65;
    int buttonY = 60;
    int offset = 45;
    int charWidth = 8;
    int charHeight = 24;
    bool checkClick = true;

    // Draw shapes
    LCD.SetDrawColor(LCD.Blue);
    LCD.FillRectangle(buttonX, buttonY, width, height);
    LCD.FillRectangle(buttonX, buttonY + offset, width, height);
    LCD.FillRectangle(buttonX, buttonY + 2 * offset, width, height);
    LCD.FillRectangle(buttonX, buttonY + 3 * offset, width, height);

    // Write text
    LCD.SetFontColor(LCD.White); 
    LCD.WriteAt("DEEP SPACE DODGE", 80, 25);
    LCD.WriteAt("Play", buttonX + (width - 4 * charWidth) / 2, buttonY + (height - charHeight));
    LCD.WriteAt("View Stats", buttonX + (width - 10 * charWidth) / 2, buttonY + offset + (height - charHeight));
    LCD.WriteAt("View Instructions", buttonX + (width - 17 * charWidth) / 2, buttonY + 2 * offset + (height - charHeight));
    LCD.WriteAt("View Credits", buttonX + (width - 12 * charWidth) / 2, buttonY + 3 * offset + (height - charHeight));

    // Check for clicks and call appropiate functions
    while (checkClick) {
        // Declare variables
        int x, y;

        // Wait for user to click screen
        LCD.ClearBuffer();
        while(!LCD.Touch(&x, &y));
        while(LCD.Touch(&x, &y));

        // Check if x position corresponds to a possible button click first
        if (x > buttonX && x < (buttonX + width)) {
            // Check the y position to determine which button was clicked
            if (y > buttonY && y < buttonY + height) {
                doGame();
            } else if (y > buttonY + offset && y < buttonY + offset + height) {
                showStatistics(0);
            } else if (y > buttonY + 2 * offset && y < buttonY + 2 * offset + offset) {
                showInstructions();
            } else if (y > buttonY + 3 * offset && y < buttonY + 3 * offset + offset) {
                showCredits();
            }
        }
    }
}

/**
 * Begins gameplay
 */
int Game::doGame() {
    LCD.Clear();

    // Write Text
    LCD.WriteLine("Play game here.");
    LCD.WriteLine("Touch anywhere to return.");

    // Declare variables
    int x,y;

    // Wait for user to click screen to return to menu
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    showMenuScreen();
    return 0;
}

/**
 * Displays statistics screen.
 */
void Game::showStatistics(int lastRunScore) {
    LCD.Clear();

    // Declare variables
    int x, y;

    // Write Text
    LCD.WriteLine("STATISTICS");
    LCD.WriteLine("High Score Leaderboard");
    LCD.WriteLine("Furthest Distances:");
    LCD.WriteLine("");
    LCD.WriteLine("1 Peter - 125 km");
    LCD.WriteLine("2 Angus - 101 km");
    LCD.WriteLine("3 Robert - 94 km");
    LCD.WriteLine("");
    LCD.WriteLine("Click anywhere to return to the menu");

    // Wait for user to click screen to return to menu
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    showMenuScreen();
}

/**
 * Displays instructions screen.
 */
void Game::showInstructions() {
    LCD.Clear();

    // Declare variables
    int x, y;

    // Write Text
    LCD.WriteLine("INSTRUCTIONS");
    LCD.WriteLine("Your job is to avoid the asteroid debris.");
    LCD.WriteLine("Tap anywhere to fire the rocket's");
    LCD.WriteLine("thrusters for a short period of time.");
    LCD.WriteLine("Gain points by escaping the asteroids.");
    LCD.WriteLine("");
    LCD.WriteLine("Click anywhere to return to the menu");

    // Wait for user to click screen to return to menu
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    showMenuScreen();
}

/**
 * Displays instructions screen.
 */
void Game::showCredits() {
    LCD.Clear();

    // Declare variables
    int x, y;

    // Write Text
    LCD.WriteLine("CREDITS");
    LCD.WriteLine("Robert Pafford");
    LCD.WriteLine("Angus Harrop");
    LCD.WriteLine("Peter Hall");
    LCD.WriteLine("");
    LCD.WriteLine("Built using the Proteus Simulator Board");
    LCD.WriteLine("feh.osu.edu/simulator_docs/");

    // Wait for user to click screen to return to menu
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    showMenuScreen();
}
