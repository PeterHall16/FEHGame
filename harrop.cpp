#include "DeepSpaceDodge.h"
#include "FEHLCD.h"
#include "cmath"
void Game::showStatistics(int lastRunScore){
    LCD.WriteLine("High Scores");
    for(int i=0; i<5; i++){
        LCD.WriteLine(highscore[i]);
    }
    LCD.Write("Last Run Score: ");
    LCD.Write(lastRunScore);
}

int Player::getHorizontalDistance(){
    roundedPosition=round(horizontalPosition);
    return roundedPosition;
}

int Player::getHeight(){
    roundedHeight=round(verticalPosition);
    return roundedHeight;
}

void Player::setDead(){
    isDead=true;
}