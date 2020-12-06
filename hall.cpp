/***********************************************/
/*    Name:  Peter Hall   Date:  12/1/20       */
/*    Seat:  12    File:  hall.cpp             */   
/*    Instructor:  Clingan 10:20               */   
/***********************************************/

#include "FEHLCD.h"
#include "FEHRandom.h"
#include "LCDColors.h"
#include "DeepSpaceDodge.h"
#include <math.h>

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
                showStatistics();
            } else if (y > buttonY + 2 * offset && y < buttonY + 2 * offset + offset) {
                showInstructions();
            } else if (y > buttonY + 3 * offset && y < buttonY + 3 * offset + offset) {
                showCredits();
            }
        }
    }
}  

/**
 * Shows instructions.
 */
void Game::showInstructions() {
    LCD.Clear();

    // Declare variables
    int x, y;

    // Write Text
    LCD.WriteLine("");
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteLine("***********INSTRUCTIONS***********");
    LCD.SetFontColor(LCD.White);
    LCD.WriteLine("  Your job is to avoid the asteroid debris.");
    LCD.WriteLine("  Tap anywhere to fire the rocket's");
    LCD.WriteLine("  thrusters for a short period of time.");
    LCD.WriteLine("  Gain points by escaping the asteroids.");
    LCD.WriteLine("");
    LCD.WriteLine("  Click anywhere to return to the menu");

    // Wait for user to click screen
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    showMenuScreen();
}

/**
 * Shows credits
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

    // Wait for user to click screen
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    showMenuScreen();
}

/***************************************************************/

/**
 * Player constructor. Initialize to passed values
 */
Player::Player(double a, double b, double c, int d, int e, bool f) {
    horizontalPosition = a;
    verticalPosition = b;
    verticalVelocity = c;
    width = d;
    height = e;
    isDead = f;
}

/**
 * Draws player
 */
bool Player::draw() {
    bool onScreen = true;

    // Adjust position to center of player
    int newVerticalPosition = round(verticalPosition - height / 2);
    int newHorizontalPosition = round(PLAYER_HORIZONTAL_POSITION - width / 2);

    // Check if player is offscreen
    if (verticalPosition < height / 2 || verticalPosition > 240 - height / 2) {
        onScreen = false;
        LCD.Clear();
    }
    
    // Draw player (rectangle for now)
    if (onScreen) {
        LCD.SetDrawColor(RED);
        LCD.DrawLine(newHorizontalPosition, newVerticalPosition + 7, newHorizontalPosition + width / 2, newVerticalPosition);
        LCD.DrawLine(newHorizontalPosition + width, newVerticalPosition + 7, newHorizontalPosition + width / 2, newVerticalPosition);
        LCD.DrawRectangle(newHorizontalPosition, newVerticalPosition + 7, width, height - 7);

        
    }

    return onScreen;
}

/**
 * Increases the verticalVelocity variable for each jump                
 */
void Player::boost() {
    verticalVelocity += PLAYER_VERTICAL_JUMP_ACCELERATION;
}
      