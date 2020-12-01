#ifndef _DEEP_SPACE_DODGE_H
#define _DEEP_SPACE_DODGE_H

class Game {
private:
    int numHighScores;
    int highScore[5];
public:
    void showMenuScreen();
    void showStatistics(int lastRunScore);
    int doGame();
};

class Player {
private:
    int horizontalPosition;
    int verticalPosition;
    int verticalVelocity;
    bool isDead;
public:
    Player();
    void jump();
    int getHorizontalDistance();
    void updatePosition();
    bool draw();
    void setDead();
};

class Obstacle {
private:
    int horizontalPosition;
    int verticalPosition;
    int radius;
public:
    Obstacle(int playerHorizontalPosition);
    bool draw(int playerHorizontalPosition);
    bool hasCollided(int playerHorizontalPosition, int playerVerticalPosition);
};

#endif