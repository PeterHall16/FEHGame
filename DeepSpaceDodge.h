#ifndef _DEEP_SPACE_DODGE_H
#define _DEEP_SPACE_DODGE_H

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_ASTEROIDS 30
#define ASTEROID_PROBABILITY 10
#define ASTEROID_MINIMUM_SIZE 5
#define ASTEROID_MAXIMUM_SIZE 15

class Game {
private:
    int numHighScores;
    int highScore[5];
public:
    void showMenuScreen();
    void showStatistics(int lastRunScore);
    void showInstructions();
    void showCredits();
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
    void boost();
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