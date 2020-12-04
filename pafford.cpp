#include <stdlib.h>
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHUtility.h"
#include "DeepSpaceDodge.h"
#include <cmath>

#include <stdio.h>

struct AsteroidNode {
    Obstacle* thisAsteroid;
    AsteroidNode* nextNode;
    AsteroidNode* prevNode;
};
AsteroidNode *asteroidHead;

/*
 * Adds a new asteroid to the front of the linked list
 * Programmed by Robert Pafford
 */
void insertAsteroid(Obstacle* asteroid) {
    if (asteroid == NULL)
        return;

    // Create the new linked list node
    AsteroidNode* node = (AsteroidNode*) calloc(1, sizeof(AsteroidNode));
    node->thisAsteroid = asteroid;
    node->prevNode = NULL;
    node->nextNode = asteroidHead;

    if (asteroidHead != NULL) {
        // Fix the previous head to point to the new head if it exists
        asteroidHead->prevNode = node;
    }

    // Set this node as the new head
    asteroidHead = node;
}

/*
 * Removes a specific asteroid from the linked list
 * Programmed by Robert Pafford
 */
void removeAsteroid(AsteroidNode* node) {
    // Make sure current node isn't null
    if (node == NULL)
        return;
    
    // If there is no previous node, it is the head, so set the head to the next node
    if (node == asteroidHead) {
        asteroidHead = node->nextNode;
    } else {
        // If there is a previous node, set the next node to this node's next node
        node->prevNode->nextNode = node->nextNode;
    }

    // If there is a next node, set its previous node to this node's previous node
    if (node->nextNode != NULL) {
        node->nextNode->prevNode = node->prevNode;
    }

    // If this asteroid isn't currently null, delete it
    if (node->thisAsteroid != NULL) {
        delete node->thisAsteroid;
    }

    // Free this node
    free(node);
}

/*
 * Clears all asteroids from linked list
 * Programmed by Robert Pafford
 */
void clearAsteroids() {
    // Loop through the asteroids deleting each one
    AsteroidNode* node = asteroidHead;
    AsteroidNode* nextNode = NULL;
    while (node != NULL) {
        nextNode = node->nextNode;
        removeAsteroid(node);
        node = nextNode;
    }
}

/*
 * Main game loop, manages the running game
 * Programmed by Robert Pafford
 */
void Game::doGame() {
    // Create player object
    Player *rocket = new Player();

    // Define variables persistent across loops
    bool stop = false;                                          // Defines when the game loop should enter death animation
    int xPos, yPos;                                             // x and y position for touch
    int touchCooldownCounter = CLICK_COOLDOWN;                  // Cooldown until another touch is allowed in ticks
    int tickStartMs = 0;                                        // Time of tick start, used for timing the game loop
    int forceAsteroidCounter = ASTEROID_INITIAL_SPAWN_DELAY;    // Time until an asteroid will be forcibly spawned in ticks
    int asteroidSpawnCooldown = ASTEROID_INITIAL_SPAWN_DELAY;   // Time until an asteroid is allowed to be spawned in ticks

    // Wait for first touch to start the game
    LCD.Clear();
    LCD.WriteAt("Tap to Start", SCREEN_WIDTH/2 - 42, SCREEN_HEIGHT/4);
    rocket->draw();
    while (!LCD.Touch(&xPos, &yPos)) {}
    LCD.ClearBuffer();

    // Main game loop
    while (true) {
        // Get the time the tick started for timing
        tickStartMs = TimeNow() * 1000;

        // Generate a random number to see if a new asteroid should be created
        // Also checks if the force asteroid counter has gone off which would require an asteroid to appear
        // Also checks if it is in the death sequence or there is a spawn cooldown which should not have asteroids spawn
        int randomSpawnChance = RandInt() % ASTEROID_PROBABILITY;
        if (!stop && asteroidSpawnCooldown <= 0 && (randomSpawnChance == 0 || forceAsteroidCounter <= 0)) {
            // Randomly generate a new time for a force spawn of an asteroid
            forceAsteroidCounter = (RandInt() % (MAX_RAND_FORCE_ASTEROID_TICKS - MIN_RAND_FORCE_ASTEROID_TICKS)) + MIN_RAND_FORCE_ASTEROID_TICKS;
            // Create the new asteroid
            Obstacle* newAsteroid = new Obstacle(rocket->getHorizontalDistance());
            insertAsteroid(newAsteroid);
            asteroidSpawnCooldown = 0;
        } else {
            // Decrement the timers if an asteroid wasn't spawned
            forceAsteroidCounter--;
            asteroidSpawnCooldown--;
        }

        // Decrement touch cooldown if it needs to be decremented
        if (touchCooldownCounter != 0) {
            touchCooldownCounter--;
        }

        // If the player touched the screen, the touch cooldown isn't active, and the player is still alive
        if (LCD.Touch(&xPos, &yPos) && touchCooldownCounter == 0 && !stop){
            // Boost the rocket, set the touch cooldown, and clear any remaining touches
            rocket->boost();
            touchCooldownCounter = CLICK_COOLDOWN;
            LCD.ClearBuffer();
        }

        // Update rocket motion and draw the rocket
        rocket->updatePosition();
        
        // Clear LCD for new game loop
        LCD.Clear();

        // Draw the rocket. If it is off the screen, end the game
        if (!rocket->draw()) {
            rocket->setDead();
            stop = true;
            break;
        }

        // Iterate through all of the asteroids
        int rocketHorizontalPosition = rocket->getHorizontalDistance();
        int rocketVerticalPosition = rocket->getHeight();
        AsteroidNode* node = asteroidHead;
        while (node != NULL) {
            // If the asteroid is no longer on the screen, remove it
            if (!node->thisAsteroid->draw(rocketHorizontalPosition)) {
                AsteroidNode* nextNode = node->nextNode;
                removeAsteroid(node);
                node = nextNode;
                continue;
            }

            // If the rocket has collided with an asteroid and the player is still alive, kill the player and begin the death sequence
            if (!stop && node->thisAsteroid->hasCollided(rocketHorizontalPosition, rocketVerticalPosition)) {
                stop = true;
                rocket->setDead();
            }

            node = node->nextNode;
        }

        // Wait until the game loop has run for the tick duration
        while (((int)(TimeNow() * 1000)) - tickStartMs < TICK_DURATION_MS) {}
    }

    // Clear screen after death
    LCD.Clear();

    // Remove any remaining asteroids from the link list
    clearAsteroids();

    // Get the score from the distance the player has traveled, then delete the player
    lastRunScore = rocket->getHorizontalDistance();
    delete rocket;

    // Recalculate the high scores with the new score, then show the statistics screen
    calculateHighScores();
    showStatistics();
}

/*
 * Updates all of the position and velocity variables of the player, taking into account gravity
 * Programmed by Robert Pafford
 */
void Player::updatePosition() {
    // If the player is not dead, move the player forward
    if (!isDead) {
        // Change position by the defined pixels/tick
        horizontalPosition += PLAYER_HORIZONTAL_VELOCITY;

        // Decrease vertical velocity by given pixels/tick^2
        verticalVelocity -= PLAYER_VERTICAL_GRAVITATIONAL_ACCELERATION;
    }
    else {
        // If the player is dead, increase the drop speed
        verticalVelocity -= PLAYER_VERTICAL_DEATH_ACCELERATION;
    }
    
    // Change position by verticalVelocity's pixels/tick
    verticalPosition -= verticalVelocity;
}

/*
 * Initializes new obstacle object, calculating and randomly generating its position and size
 * Programmed by Robert Pafford
 */
Obstacle::Obstacle(int playerHorizontalPosition) {
    // Generate random radius between minimum and maximum size
    radius = (RandInt() % (ASTEROID_MAXIMUM_SIZE - ASTEROID_MINIMUM_SIZE)) + ASTEROID_MINIMUM_SIZE;

    // Calculate horizontal position at the edge of the screen, based on the player's position
    horizontalPosition = playerHorizontalPosition + PLAYER_HORIZONTAL_POSITION - radius;

    // Generate random vertical position between the edges of the screen
    verticalPosition = (RandInt() % (SCREEN_HEIGHT - radius * 2)) + radius;

    // Initialize all other class variables to default values
    collisionOccurred = false;
    explosionCompleted = false;
}

/*
 * Checks if the player has collided with this asteroid
 * Programmed by Robert Pafford
 */
bool Obstacle::hasCollided(int playerHorizontalPosition, int playerVerticalPosition) {
    // Calclate the corners of the player
    double playerCorners[4][2] = {{playerHorizontalPosition + (PLAYER_WIDTH/2.0), playerVerticalPosition + (PLAYER_HEIGHT/2.0)}, {playerHorizontalPosition - (PLAYER_WIDTH/2.0), playerVerticalPosition + (PLAYER_HEIGHT/2.0)},
                                  {playerHorizontalPosition + (PLAYER_WIDTH/2.0), playerVerticalPosition - (PLAYER_HEIGHT/2.0)}, {playerHorizontalPosition - (PLAYER_WIDTH/2.0), playerVerticalPosition - (PLAYER_HEIGHT/2.0)}};
    
    // Check if any corner is within the radius of the asteroid
    for (int corner = 0; corner < 4; corner++) {
        if ((pow(round(playerCorners[corner][0]) - horizontalPosition, 2) + pow(round(playerCorners[corner][1]) - verticalPosition, 2)) < pow(radius, 2)) {
            // Mark the collision variable to animate asteroid explosion, then return true for a collision
            collisionOccurred = true;
            return true;
        }
    }

    return false;
}