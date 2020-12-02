#include "DeepSpaceDodge.h"
#include "FEHLCD.h"
#include "cmath"

void Game::showStatistics(){

    //Clear Screen
    LCD.Clear();

    //Declare variables
    int x, y;

    //Write text
    LCD.WriteLine("High Score Leaderboard");
    LCD.WriteLine("Furthest Distances:");

    //display top 5 scores from all runs
    for(int i=0; i<5; i++){            
        LCD.Write(i+1);
        LCD.Write(" - ");
        LCD.WriteLine(highScore[i]);
    }
    //display latest run score
    LCD.Write("Last Run Score: ");
    LCD.WriteLine(lastRunScore);

    //Wait for user touch to return to main screen
    LCD.WriteLine("Click anywhere to return to the menu");
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    showMenuScreen();
}

int Player::getHorizontalDistance(){

    //round and return the horizontal position of the player
    int roundedVerticalPosition=round(horizontalPosition);
    return roundedVerticalPosition;
}

int Player::getHeight(){

    //round and return the vertical position of the player
    int roundedHeight=round(verticalPosition);
    return roundedHeight;
}

void Player::setDead(){

    //Set the dead condition of the player to true
    isDead=true;
}

bool Obstacle::draw(int playerHorizontalPosition){

    //Calculate the x coordinate of the center of the obstacle
    int x_position=playerHorizontalPosition-horizontalPosition+PLAYER_HORIZONTAL_POSITION;

    //if the obstacle is off of the screen return false, if it is on the screen, return true;
    if(x_position-radius<0){
        return false;
    }
    else{
        //draw the obstacle in the set position based on the horizontal position of the player
        LCD.FillCircle(x_position,verticalPosition,radius);
        return true;
    }
}

void Game::calculateHighScores() {

}