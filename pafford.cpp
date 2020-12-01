#include <stdlib.h>
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHUtility.h"
#include "DeepSpaceDodge.h"

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

int Game::doGame() {
    LCD.Clear();
    LCD.WriteLine("Play game here. Touch anywhere to quit");
    int x,y;
    while (LCD.Touch(&x, &y));
    Sleep(250);
    while (!LCD.Touch(&x, &y));
    while (LCD.Touch(&x, &y));
    return 0;
}

/*
int Game::doGame() {
    // Create player object
    Player *rocket = new Player();

    // Define variables persistent across loops
    bool stop = false;
    int touchCooldownCounter = 0;

    int tickStartMs = 0;

    // Main game loop
    while (true) {
        tickStartMs = TimeNow() * 1000;
        // Clear LCD for new game loop
        LCD.Clear();

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
            touchCooldownCounter = 5;
        }

        // Update rocket motion and draw the rocket
        rocket->updatePosition();

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
            if (node->thisAsteroid->hasCollided(rocketHorizontalPosition, rocketVerticalPosition) && !stop) {
                stop = true;
            }

            node = node->nextNode;
        }

        while (((int)(TimeNow() * 1000)) - tickStartMs < TICK_DURATION_MS) {}
    }

    LCD.Clear();

    return rocket->getHorizontalDistance();
}*/