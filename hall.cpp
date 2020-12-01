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
    int buttonWidth = 220;
    int buttonHeight = 45;
    int buttonXPos = 50;
    int buttonYPos = 60;
    int buttonOffset = 60;

    bool checkClick = true;

    // Draw shapes
    LCD.DrawRectangle(buttonXPos, buttonYPos, buttonWidth, buttonHeight);
    LCD.DrawRectangle(buttonXPos, buttonYPos + 60, buttonWidth, buttonHeight);
    LCD.DrawRectangle(buttonXPos, buttonYPos + 120, buttonWidth, buttonHeight);

    // Write text
    LCD.Write("DEEP SPACE DODGE");

    // Check for clicks and call appropiate functions
    while (checkClick) {
        // Declare variables
        int x, y;

        // Wait for user to click screen
        while(!LCD.Touch(&x, &y));

        // Check if x position corresponds to a possible button click first
        if (x > buttonXPos && x < buttonWidth) {
            // Check the y position to determine which button was clicked
            
        }
    }
}