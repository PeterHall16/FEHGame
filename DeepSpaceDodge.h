#ifndef _DEEP_SPACE_DODGE_H
#define _DEEP_SPACE_DODGE_H

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define PLAYER_HORIZONTAL_VELOCITY 2.0      // Velocity in pixels/tick
#define PLAYER_VERTICAL_ACCELERATION 2.0    // Acceleration in pixels/tick^2

#define TICK_DURATION_MS 20
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
    double horizontalPosition;
    double verticalPosition;
    double verticalVelocity;
    bool isDead;
public:
    Player();
    void boost();
    int getHorizontalDistance();
    int getHeight();
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