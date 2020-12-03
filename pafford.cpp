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

void Game::doGame() {

    // Create player object
    Player *rocket = new Player();

    // Define variables persistent across loops
    bool stop = false;
    int touchCooldownCounter = 0;

    int tickStartMs = 0;

    // Main game loop
    while (true) {
        tickStartMs = TimeNow() * 1000;

        // Generate a random number to see if a new asteroid should be created
        // Also checks if it is in the death sequence since no new asteroids should appear then
        int randomSpawnChance = RandInt() % ASTEROID_PROBABILITY;
        if (randomSpawnChance == 0 && !stop) {
            Obstacle* newAsteroid = new Obstacle(rocket->getHorizontalDistance());
            insertAsteroid(newAsteroid);
        }

        // Decrement touch cooldown if it needs to be decremented
        if (touchCooldownCounter != 0) {
            touchCooldownCounter--;
        }

        // If the player touched the screen, the touch cooldown isn't active, and the player is still alive
        int xPos, yPos;
        if (LCD.Touch(&xPos, &yPos) && touchCooldownCounter == 0 && !stop){
            rocket->boost();
            touchCooldownCounter = CLICK_COOLDOWN;
        }
        LCD.ClearBuffer();

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

        while (((int)(TimeNow() * 1000)) - tickStartMs < TICK_DURATION_MS) {}
    }

    LCD.Clear();

    delete rocket;

    lastRunScore = rocket->getHorizontalDistance();
    calculateHighScores();
    showStatistics();
}

void Player::updatePosition() {
    // If the player is not dead, move the player forward
    if (!isDead) {
        // Change position by the defined pixels/tick
        horizontalPosition += PLAYER_HORIZONTAL_VELOCITY;
    }

    // Decrease vertical velocity by given pixels/tick^2
    verticalVelocity -= PLAYER_VERTICAL_GRAVITATIONAL_ACCELERATION;
    
    // Change position by verticalVelocity's pixels/tick
    verticalPosition -= verticalVelocity;
}

Obstacle::Obstacle(int playerHorizontalPosition) {
    // Generate Radius
    radius = (RandInt() % (ASTEROID_MAXIMUM_SIZE - ASTEROID_MINIMUM_SIZE)) + ASTEROID_MINIMUM_SIZE;

    // Calculate horizontal position
    horizontalPosition = playerHorizontalPosition + PLAYER_HORIZONTAL_POSITION - radius;

    // Generate random vertical position
    verticalPosition = (RandInt() % (SCREEN_HEIGHT - radius * 2)) + radius;
}

bool Obstacle::hasCollided(int playerHorizontalPosition, int playerVerticalPosition) {
    // Calclate the corners of the player
    double playerCorners[4][2] = {{playerHorizontalPosition + (PLAYER_WIDTH/2.0), playerVerticalPosition + (PLAYER_HEIGHT/2.0)}, {playerHorizontalPosition - (PLAYER_WIDTH/2.0), playerVerticalPosition + (PLAYER_HEIGHT/2.0)},
                               {playerHorizontalPosition + (PLAYER_WIDTH/2.0), playerVerticalPosition - (PLAYER_HEIGHT/2.0)}, {playerHorizontalPosition - (PLAYER_WIDTH/2.0), playerVerticalPosition - (PLAYER_HEIGHT/2.0)}};
    
    // Check if any corner is within the radius of the asteroid
    for (int corner = 0; corner < 4; corner++) {
        if ((pow(round(playerCorners[corner][0]) - horizontalPosition, 2) + pow(round(playerCorners[corner][1]) - verticalPosition, 2)) < pow(radius, 2)) {
            return true;
        }
    }

    return false;
}