#include "DeepSpaceDodge.h"
#include "FEHLCD.h"
#include "cmath"

void Game::showStatistics(){

    //Declare variables
    int x, y;

    //Clear Screen
    LCD.Clear();

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
    //Set player velocity to zero
    verticalVelocity=0;
    //Set the dead condition of the player to true
    isDead=true;
}

bool Obstacle::draw(int playerHorizontalPosition){

    //Calculate the x coordinate of the center of the obstacle
    int x_position=playerHorizontalPosition-horizontalPosition+PLAYER_HORIZONTAL_POSITION;

    //if the obstacle is off of the screen return false, if it is on the screen, return true;
    if(x_position+radius>SCREEN_WIDTH){
        return false;
    }
    else{
        //Set color of obstacles to gray
        LCD.SetDrawColor(GRAY);
        //draw the obstacle in the set position based on the horizontal position of the player
        LCD.FillCircle(x_position,verticalPosition,radius);
        return true;
    }
}

void Game::calculateHighScores() {
    //Check to see if the last run score is a high score and place it in the correct spot if it is
    for(int i =0; i<5; i++){
        if(lastRunScore>highScore[i]){
            for(int j=4; j>i; j--){
                highScore[j]=highScore[j-1];
            }
            highScore[i]=lastRunScore;
            break;
        }
    }
}