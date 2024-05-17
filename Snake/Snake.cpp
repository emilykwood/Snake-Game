#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

// Function declarations
void initGameVariables();
void renderInitialScreen();
void hideCursor();
void renderDynamicElements();
int _getch();

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// Game space size
int gameHeight = 20;
int gameWidth = 80;
int score = 0;

int xPos, yPos; // Snake head position
std::string fruit = "*";
int fruitX, fruitY; // Fruit position
enum snakeDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakeDirection snakeDir;
bool isGameOver;

const int maxSnakeLength = 100; // Maximum length of the snake
std::pair<int, int> snakeBody[maxSnakeLength]; // Array to store snake's body
int snakeLength = 1; // Initial length of the snake

void initGameVariables() {
    // need to include this function which seeds the random number generator using the time, in order to truly get a random int
    srand(static_cast<unsigned int>(time(0)));
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

void setCursorPosition(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(consoleHandle, cursorPosition);
}

void renderInitialScreen() {
    hideCursor();

    // Draw top border
    for (int i = 0; i < gameWidth; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;

    // Draw side borders and initial empty space
    for (int i = 0; i < gameHeight; i++) {
        std::cout << "|";
        for (int j = 0; j < gameWidth - 2; j++) {
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }

    // Draw bottom border
    for (int i = 0; i < gameWidth; i++) {
        std::cout << "-";
    }
}

void renderDynamicElements() {
    // Draw snake body
    for (int i = 0; i < snakeLength; i++) {
        setCursorPosition(snakeBody[i].second, snakeBody[i].first);
        std::cout << "O";
    }

    // Draw fruit
    setCursorPosition(fruitX, fruitY);
    std::cout << fruit;

    // Update score
    setCursorPosition(0, gameHeight + 1);
    std::cout << "\nScore: " << score;

}

void userInput() {
    if (_kbhit()) {
        switch (_getch()) {
        case KEY_UP:
            if (snakeDir != DOWN) snakeDir = UP;
            break;
        case KEY_DOWN:
            if (snakeDir != UP) snakeDir = DOWN;
            break;
        case KEY_LEFT:
            if (snakeDir != RIGHT) snakeDir = LEFT;
            break;
        case KEY_RIGHT:
            if (snakeDir != LEFT) snakeDir = RIGHT;
            break;
        }
    }
}

void updateGameState() {
    // Update snake's position based on direction
    //What were it's previous co-ordinates
    std::pair<int, int> prevTailCoords = snakeBody[snakeLength - 1];

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
        fruitX = rand() % gameWidth;
        fruitY = rand() % gameHeight;
        snakeLength++;
    }

    // Check for collision with walls
    if (xPos <= 0 || xPos >= gameWidth - 1 || yPos <= 0 || yPos >= gameHeight) {
        isGameOver = true;
    }

    // Check for collision with itself
    for (int i = 1; i < snakeLength; i++) {
        if (snakeBody[i].first == yPos && snakeBody[i].second == xPos) {
            isGameOver = true;
        }
    }

    // Move the snake's body
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeBody[i] = snakeBody[i - 1];
    }
    snakeBody[0] = { yPos, xPos };

    //clear the previous end of the snake 
    setCursorPosition(prevTailCoords.second, prevTailCoords.first);
    std::cout << " ";
}

int main() {
    initGameVariables();
    renderInitialScreen();

    while (!isGameOver) {
        userInput();
        updateGameState();
        renderDynamicElements();
        Sleep(150); // Adjust the frame rate
    }

    setCursorPosition(0, gameHeight + 2);
    std::cout << "Game over! Your Score: " << score << std::endl;

    return 0;
}
