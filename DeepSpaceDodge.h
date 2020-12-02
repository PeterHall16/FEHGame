#ifndef _DEEP_SPACE_DODGE_H
#define _DEEP_SPACE_DODGE_H

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define PLAYER_HORIZONTAL_VELOCITY 2.0      // Velocity in pixels/tick
#define PLAYER_STARTING_VERTICAL_VELOCITY 0.0
#define PLAYER_VERTICAL_JUMP_ACCELERATION 12
#define PLAYER_VERTICAL_GRAVITATIONAL_ACCELERATION 2.0    // Acceleration in pixels/tick^2

#define PLAYER_STARTING_VERTICAL_POSITION 120
#define PLAYER_HORIZONTAL_POSITION 160

#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 20

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
    int width;
    int height;
    bool isDead;
public:
    Player(double = PLAYER_HORIZONTAL_POSITION, double = PLAYER_STARTING_VERTICAL_POSITION, 
    double = PLAYER_STARTING_VERTICAL_VELOCITY, int = PLAYER_WIDTH, int = PLAYER_HEIGHT, bool = false);
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