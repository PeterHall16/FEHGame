#include "DeepSpaceDodge.h"
#include "FEHLCD.h"
#include "cmath"
void Game::showStatistics(int lastRunScore){
    LCD.WriteLine("High Scores");
    for(int i=0; i<5; i++){
        LCD.WriteLine(highScore[i]);
    }
    LCD.Write("Last Run Score: ");
    LCD.Write(lastRunScore);
}

int Player::getHorizontalDistance(){
    int roundedPosition=round(horizontalPosition);
    return roundedPosition;
}

int Player::getHeight(){
    int roundedHeight=round(verticalPosition);
    return roundedHeight;
}

void Player::setDead(){
    isDead=true;
}