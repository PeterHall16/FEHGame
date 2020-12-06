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

/*
 * Displays the menu screen
 * Programmed by Peter Hall
 */
void Game::showMenuScreen() {
    // Clear the menu screen
    LCD.Clear();

    // Define variables used for displaying the menu
    int width = 190;
    int height = 35;
    int buttonX = 65;
    int buttonY = 60;
    int offset = 45;
    int charWidth = 8;
    int charHeight = 24;

    // Draw menu buttons
    LCD.SetDrawColor(LCD.Blue);
    LCD.FillRectangle(buttonX, buttonY, width, height);
    LCD.FillRectangle(buttonX, buttonY + offset, width, height);
    LCD.FillRectangle(buttonX, buttonY + 2 * offset, width, height);
    LCD.FillRectangle(buttonX, buttonY + 3 * offset, width, height);

    // Write title and menu labels
    LCD.SetFontColor(LCD.White); 
    LCD.WriteAt("DEEP SPACE DODGE", 83, 25);
    LCD.WriteAt("Play", buttonX + (width - 4 * charWidth) / 2, buttonY + (height - charHeight));
    LCD.WriteAt("View Stats", buttonX + (width - 10 * charWidth) / 2, buttonY + offset + (height - charHeight));
    LCD.WriteAt("View Instructions", buttonX + (width - 17 * charWidth) / 2, buttonY + 2 * offset + (height - charHeight));
    LCD.WriteAt("View Credits", buttonX + (width - 12 * charWidth) / 2, buttonY + 3 * offset + (height - charHeight));

    // Check for clicks and call appropiate functions
    // Declare variables used for registering a touch
    int x, y;

    // Wait for user to click screen
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));

    // Check if x position corresponds to a possible button click first
    if (x > buttonX && x < (buttonX + width)) {
        // Check the y position to determine which button was clicked
        if (y > buttonY && y < buttonY + height) {
            doGame(); // Begin gameplay
        } else if (y > buttonY + offset && y < buttonY + offset + height) {
            showStatistics(); // Display the statistics screen
        } else if (y > buttonY + 2 * offset && y < buttonY + 2 * offset + offset) {
            showInstructions(); // Display the instructions screen
        } else if (y > buttonY + 3 * offset && y < buttonY + 3 * offset + offset) {
            showCredits(); // Display the credits screen
        }
    }
}  

/*
 * Displays the game instructions
 * Programmed by Peter Hall
 */
void Game::showInstructions() {
    // Clear the menu screen
    LCD.Clear();

    // Declare variables
    int x, y;

    // Write Text
    LCD.SetFontColor(SCARLET);
    LCD.WriteAt("***********INSTRUCTIONS***********", 1, 5);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Your job is to avoid the asteroid debris.", 8, 30);
    LCD.WriteAt("Tap anywhere to fire the rocket's", 8, 52);
    LCD.WriteAt("thrusters for a short period of time.", 8, 74);
    LCD.WriteAt("Gain points by escaping the asteroids.", 8, 96);
    LCD.WriteAt("Click anywhere to return to the menu",15,220);

    // Wait for user to click screen
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));

    // Return to the menu screen
    showMenuScreen();
}

/*
 * Displays the game credits
 * Programmed by Peter Hall
 */
void Game::showCredits() {
    // Clear the menu screen
    LCD.Clear();

    // Declare variables
    int x, y;

    // Write Text
    LCD.SetFontColor(SCARLET);
    LCD.WriteAt("**************Credits***************",2,5);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Robert Pafford", 97, 30);
    LCD.WriteAt("Peter Hall", 117, 55);
    LCD.WriteAt("Angus Harrop", 101, 80);
    LCD.WriteAt("feh.osu.edu/simulator_docs", 50, 130);
    LCD.WriteAt("Click anywhere to return to the menu",15,220);

    // Wait for user to click screen
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));

    // Return to the menu screen
    showMenuScreen();
}

/*
 * Initializes the private fields of the Player class
 * Programmed by Peter Hall
 */
Player::Player(double a, double b, double c, int d, int e, bool f) {
    horizontalPosition = a;
    verticalPosition = b;
    verticalVelocity = c;
    width = d;
    height = e;
    isDead = f;
}

/*
 * Draws the player at its current location
 * Programmed by Peter Hall
 */
bool Player::draw() {
    // Initialize the player's position as on the screen
    bool onScreen = true;

    // Connvert the player's position from its center to its upper-left corner
    int newVerticalPosition = round(verticalPosition - height / 2);
    int newHorizontalPosition = round(PLAYER_HORIZONTAL_POSITION - width / 2);

    // Check if player is offscreen
    if (verticalPosition < height / 2 || verticalPosition > 240 - height / 2) {
        // Player is now inactive
        onScreen = false;
        LCD.Clear();
    } else {
        // Player is still active
        LCD.SetDrawColor(RED);
        // Draw the player
        LCD.DrawRectangle(newHorizontalPosition, newVerticalPosition, width, height);
    }

    return onScreen;
}

/*
 * Increases the player's vertical velocity
 * Programmed by Peter Hall
 */
void Player::boost() {
    // Increase the player's vertical velocity, simulating a jump/boost
    verticalVelocity += PLAYER_VERTICAL_BOOST_ACCELERATION;
}
      