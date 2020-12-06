#include "DeepSpaceDodge.h"
#include "FEHLCD.h"
#include "cmath"
#include "FEHSD.h"

/*
*Displays statistics menu and the high scores
*Programmed by Angus Harrop
*/
void Game::showStatistics(){

    //Clear Screen
    LCD.Clear();

    //Declare variables for user touch
    int x, y;

    //Write statistics menu text
    LCD.SetFontColor(SCARLET);
    LCD.WriteAt("*******High Score Leaderboard*******",2,5);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Rank",75,30);
    LCD.WriteAt("Score",204,30);
    LCD.SetDrawColor(WHITE);
    LCD.DrawHorizontalLine(46,72,115);
    LCD.DrawHorizontalLine(46,189,262);

    //display top 5 scores from all runs
    for(int i=0; i<5; i++){         
        LCD.WriteAt(i+1,88,56+25*i);
        LCD.WriteAt(highScore[i],190,56+25*i);
        LCD.WriteAt(" PTS",230,56+25*i);
    }

    //display latest run score
    LCD.SetFontColor(SCARLET);
    LCD.WriteAt("Last Run Score: ",10,188);
    LCD.WriteAt(lastRunScore,135,188);
    LCD.WriteAt(" PTS",175,188);

    //Wait for user touch to return to main screen
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Click anywhere to return to the menu",15,220);
    LCD.ClearBuffer();
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    showMenuScreen();
}

/*
*Returns the horizontal distance of the player object
*Programmed by Angus Harrop
*/
int Player::getHorizontalDistance(){

    //round and return the horizontal position of the player
    int roundedHorizontalPosition=round(horizontalPosition);
    return roundedHorizontalPosition;
}

/*
*Returns the height of the player object
*Programmed by Angus Harrop
*/
int Player::getHeight(){

    //round and return the vertical position of the player
    int roundedHeight=round(verticalPosition);
    return roundedHeight;
}

/*
*Sets the player object to start its death process
*Programmed by Angus Harrop
*/
void Player::setDead(){

    //Set player velocity to zero
    verticalVelocity=0;

    //Set the dead condition of the player to true
    isDead=true;
}

/*
*Draws the obstacle object at the specified location with a specified color
*Programmed by Angus Harrop
*/
bool Obstacle::draw(int playerHorizontalPosition){

    //Calculate the x coordinate of the center of the obstacle
    int x_position=playerHorizontalPosition-horizontalPosition+PLAYER_HORIZONTAL_POSITION;

    //if the obstacle is off of the screen, return false. if it is on the screen, return true
    if(x_position+radius>=SCREEN_WIDTH){
        return false;
    }
    else if(collisionOccurred && !explosionCompleted){

        //Change the color of the obstacle to yellow when colliding with the player
        LCD.SetDrawColor(YELLOW);

        //Make the object delete itself next time it is drawn
        explosionCompleted=true;
    }
    else if(explosionCompleted){

        //Set the obstacle to delete itself
        return false;
    }
    else{

        //Set the color of the obstacle to gray
        LCD.SetDrawColor(GRAY);
    }

    //draw the obstacle in its new position based on the horizontal position of the player
    LCD.DrawCircle(x_position,verticalPosition,radius);
    return true;
}

/*
*Inserts the last run score into the current high scores if it meets the requirements
*Programmed by Angus Harrop
*/
void Game::calculateHighScores() {

    //check to see if the last run score is a high score and place it in the correct spot if it is 
    //move the other high scores to account for the new high score 
    for(int i =0; i<5; i++){
        if(lastRunScore>highScore[i]){
            for(int j=4; j>i; j--){
                highScore[j]=highScore[j-1];
            }
            highScore[i]=lastRunScore;
            break;
        }
    }

    //Call saveHighScores() function to save the high scores to the text file
    saveHighScores();
}

/*
*Saves the current game high scores into a text file
*Programmed by Angus Harrop
*/
void Game::saveHighScores(){

    //Open up the high scores text file for writing
    FEHFile* highScores = SD.FOpen("HighScores.txt","w");

    //Write each high score from the current game into the text file
    for(int i=0; i<5; i++){
        SD.FPrintf(highScores,"%d\n",highScore[i]);
    }

    //close the text file
    SD.FClose(highScores);

}

/*
*Loads the text file high scores into the current game high scores
*Programmed by Angus Harrop
*/
void Game::loadHighScores(){

    //Open up the high scores text file for reading 
    FEHFile* highScores = SD.FOpen("HighScores.txt","r");

    //Read in each high score from the text file into the current game high scores
    for(int i=0; i<5; i++){
        SD.FScanf(highScores,"%d",&highScore[i]);
    }

    //close the text file
    SD.FClose(highScores);

}