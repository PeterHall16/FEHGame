/***********************************************/
/*    Name:  Peter Hall   Date:  12/1/20       */
/*    Seat:  12    File:  hall.cpp             */   
/*    Instructor:  Clingan 10:20               */   
/***********************************************/

#include "FEHLCD.h"
#include "DeepSpaceDodge.h"

/**
 * Displays menu screen.
 */
void Game::showMenuScreen() {
    LCD.Clear();

    // Define variables
    int displayWidth = 320;
    int displayHeight = 240;
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
        while(!LCD.Touch(&x, &y));

        // Check if x position corresponds to a possible button click first
        if (x > buttonX && x < width) {
            // Check the y position to determine which button was clicked
            if (y > buttonY && y < buttonY + height) {
                // doGame();
                checkClick = false;
            } else if (y > buttonY + offset && y < buttonY + offset + height) {
                // showStatistics();
                checkClick = false;
            } else if (y > buttonY + 2 * offset && y < buttonY + 2 * offset + offset) {
                // showInstructions();
                checkClick = false;
            } else if (y > buttonY + 3 * offset && y < buttonY + 3 * offset + offset) {
                // showCredits();

                checkClick = false;
            }
        }
    }
}