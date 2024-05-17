#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

void initGameVariables();
void renderTheGame();
void hideCursor();
int _getch();

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int gameHeight = 20;
int gameWidth = 80;
int score = 0;

int xPos, yPos;
std::string fruit = "*";
int fruitX, fruitY;
enum snakeDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakeDirection snakeDir;
bool isGameOver;

const int maxSnakeLength = 100; // Maximum length of the snake
std::pair<int, int> snakeBody[maxSnakeLength]; // Array to store snake's body
int snakeLength = 1; // Initial length of the snake

void initGameVariables() {
    isGameOver = false;
    fruitX = rand() % gameWidth;
    fruitY = rand() % gameHeight;
    xPos = gameWidth / 2;
    yPos = gameHeight / 2;
    score = 0;
    snakeDir = STOP;
    snakeLength = 1;
    snakeBody[0] = { yPos, xPos }; // Initialize snake with one segment
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void renderTheGame() {
    system("cls");
    hideCursor();

    // Now we get to drawing the borders of the game
    for (int i = 0; i < gameWidth; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int i = 0; i < gameHeight; i++) {
        for (int j = 0; j < gameWidth; j++) {
            if (j == 0 || j == gameWidth - 1) {
                std::cout << "|";
            }
            // Position fruit within the game bounds
            else if (j == fruitX && i == fruitY) {
                std::cout << fruit;
            }
            else {
                bool isSnakeBody = false;
                for (int k = 0; k < snakeLength; k++) {
                    if (j == snakeBody[k].second && i == snakeBody[k].first) {
                        isSnakeBody = true;
                        break;
                    }
                }
                std::cout << (isSnakeBody ? "O" : " ");
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < gameWidth; i++) {
        std::cout << "-";
    }
    std::cout << "\nScore: " << score;
}

void userInput() {
    if (_kbhit()) {
        switch (_getch()) {
        case KEY_UP:
            snakeDir = UP;
            break;
        case KEY_DOWN:
            snakeDir = DOWN;
            break;
        case KEY_LEFT:
            snakeDir = LEFT;
            break;
        case KEY_RIGHT:
            snakeDir = RIGHT;
            break;
        }
    }
}

void updateGameState() {
    // Update snake's position based on direction
    switch (snakeDir) {
    case UP:
        yPos--;
        break;
    case DOWN:
        yPos++;
        break;
    case LEFT:
        xPos--;
        break;
    case RIGHT:
        xPos++;
        break;
    }

    // Check for collision with fruit
    if (xPos == fruitX && yPos == fruitY) {
        score++;
        // Generate new position for the fruit
        fruitX = rand() % gameWidth;
        fruitY = rand() % gameHeight;
        // Increase snake's length
        snakeLength++;
    }

    // Move the snake's body
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeBody[i] = snakeBody[i - 1];
    }
    snakeBody[0] = { yPos, xPos };
}

int main() {
    hideCursor();
    initGameVariables();

    while (!isGameOver) {
        userInput();
        updateGameState();
        renderTheGame();
        Sleep(100); // Adjust the frame rate
    }

    std::cout << "Game over! Your Score: " << score;

    return 0;
}