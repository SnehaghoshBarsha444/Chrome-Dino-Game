#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 50
#define GROUND_Y 15
#define DINO_X 5
#define CACTUS_START 45
#define JUMP_HEIGHT 6
#define GRAVITY 1

int cactusX = CACTUS_START;
int isJumping = 0;
int jumpVelocity = 0;
int dinoY = GROUND_Y;
int score = 0;
int gameOver = 0;

// Function to introduce delay while keeping game smooth
void delay(int ms) {
    clock_t start = clock();
    while (clock() < start + ms);
}

// Function to clear screen
void clearScreen() {
    system("cls");
}

// Function to draw the game
void drawGame() {
    clearScreen();

    for (int y = 0; y <= GROUND_Y; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (x == DINO_X && y == dinoY) {
                printf("D"); // Dino
            } else if (x == cactusX && y == GROUND_Y) {
                printf("^"); // Cactus
            } else if (y == GROUND_Y) {
                printf("_"); // Ground
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Score: %d\n", score);
}

// Function to update game logic
void updateGame() {
    // Move cactus
    cactusX--;

    // Reset cactus when it moves out of the screen
    if (cactusX <= 0) {
        cactusX = CACTUS_START + (rand() % 10); // Randomize cactus position
        score++;
    }

    // Apply Gravity
    if (isJumping) {
        dinoY -= jumpVelocity;
        jumpVelocity--;

        if (jumpVelocity < -JUMP_HEIGHT) { // Falling down
            isJumping = 0;
            jumpVelocity = 0;
        }
    }

    // Ensure Dino lands correctly
    if (dinoY >= GROUND_Y) {
        dinoY = GROUND_Y;
        isJumping = 0;
    }

    // Check collision
    if (cactusX == DINO_X && dinoY == GROUND_Y) {
        gameOver = 1;
    }
}

// Function to handle input
void handleInput() {
    if (_kbhit()) {
        char key = _getch();
        if (key == ' ' && dinoY == GROUND_Y) { // Jump only if on ground
            isJumping = 1;
            jumpVelocity = JUMP_HEIGHT;
        }
    }
}

// Main function
int main() {
    srand(time(0));

    while (!gameOver) {
        drawGame();
        handleInput();
        updateGame();
        delay(50); // Smooth frame timing
    }

    clearScreen();
    printf("Game Over!\nFinal Score: %d\n", score);
    return 0;
}
