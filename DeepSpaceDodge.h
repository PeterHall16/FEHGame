#ifndef _DEEP_SPACE_DODGE_H
#define _DEEP_SPACE_DODGE_H

// Screen dimensions in pixels
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Player Velocities in pixels/tick
#define PLAYER_HORIZONTAL_VELOCITY 8.0
#define PLAYER_STARTING_VERTICAL_VELOCITY 10.0

// Player Accelerations in pixels/tick^2
#define PLAYER_VERTICAL_JUMP_ACCELERATION 14.0
#define PLAYER_VERTICAL_GRAVITATIONAL_ACCELERATION 1.5
#define PLAYER_VERTICAL_DEATH_ACCELERATION 5.0

// Player Positions in pixels
#define PLAYER_STARTING_VERTICAL_POSITION 120
#define PLAYER_HORIZONTAL_POSITION 160

// Player/Obstacle dimensions in pixels
#define PLAYER_WIDTH 14
#define PLAYER_HEIGHT 19
#define ASTEROID_MINIMUM_SIZE 15
#define ASTEROID_MAXIMUM_SIZE 35

// Timinings in ticks
#define CLICK_COOLDOWN 2                    // Cooldown until another click can happen
#define MIN_RAND_FORCE_ASTEROID_TICKS 10    // Minimum amount of time that the force asteroid cooldown can be
#define MAX_RAND_FORCE_ASTEROID_TICKS 15    // Maximum amount of time that the force asteroid cooldown can be
#define ASTEROID_INITIAL_SPAWN_DELAY 20     // Delay until asteroid is spawned at the start of the game

// Duration of one game tick in milliseconds
#define TICK_DURATION_MS 100

// 1/Probability of asteroid spawning every game tick
#define ASTEROID_PROBABILITY 30

/*
 * Main game class that manages the game and draws all of the screens
 */
class Game {
private:
    int lastRunScore;   // The score from the player's last run
    int highScore[5];   // The top 5 high scores in the game
public:
    void showMenuScreen();
    void showStatistics();
    void showInstructions();
    void showCredits();
    void calculateHighScores();
    void doGame();
    void loadHighScores();
    void saveHighScores();
};

/*
 * Player class which represents the rocket sprite on the screen
 */
class Player {
private:
    double horizontalPosition;  // The horizontal position of the player in 'virtual' space
    double verticalPosition;    // The vertical position of the player on the screen
    double verticalVelocity;    // The vertical velocity of the player
    int width;                  // The width of the player
    int height;                 // The height of the player
    bool isDead;                // Whether or not the player is dead and should be showing its death animation
    
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

/*
 * Obstacle class which represents one asteroid on the screen
 */
class Obstacle {
private:
    int horizontalPosition;     // The horizontal position of the asteroid in 'virtual' space
    int verticalPosition;       // The vertical position of the asteroid on the screen
    int radius;                 // The radius of the asteroid
    bool collisionOccurred;     // Whether or not the asteroid has collided with the player
    bool explosionCompleted;    // Whether or not the asteroid has shown the explosion animation
public:
    Obstacle(int playerHorizontalPosition);
    bool draw(int playerHorizontalPosition);
    bool hasCollided(int playerHorizontalPosition, int playerVerticalPosition);
};

#endif