#include <iostream>
#include <conio.h> 
#include <windows.h>
#include <cstdlib> 
#include <deque>

//I was getting build errors before I added this in
void initGameVariables();
void renderTheGame();
int _getch();

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// Declare the size of the game space
int gameHeight = 20;
int gameWidth = 80;
int score = 0;

int xPos, yPos; // position of the snake head
std::string fruit = "*";
int fruitX, fruitY; // holds the x and y position of the fruit the snake is trying to eat

enum snakeDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakeDirection snakeDir; //holds the value of the above
std::deque<std::pair<int, int>> snakeBody; //deque means double ended queue allows me to add body to either end of the snake dependent on direction
bool isGameOver;


void initGameVariables() {
    isGameOver = false;
    fruitX = rand() % gameWidth;
    fruitY = rand() % gameHeight;
    xPos = gameWidth / 2;
    yPos = gameHeight / 2;
    score = 0; 
    snakeDir = STOP;
    snakeBody.clear();
    snakeBody.push_front({ yPos, xPos });

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
        std::cout <<  "-";
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
                // Position snake head at centre of the screen
            } else if (j == xPos && i == yPos) {
                    std::cout << "O";
            } else {
                std::cout << " ";
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
        switch (_getch()) {
        case KEY_UP:
            std::cout << "Up";
            snakeDir = UP;
            yPos--;
            break;
        case KEY_DOWN:
            std::cout << "Down";
            snakeDir = DOWN;
            yPos++;
            break;
        case KEY_LEFT:
            std::cout << "left";
            snakeDir = LEFT;
            xPos--;
            break;
        case KEY_RIGHT:
            std::cout << "Right";
            snakeDir = RIGHT;
            xPos++;
            break;
        }

}

// Function to update the game state
void updateGameState() {

    // Check for collision with fruit
    if (xPos == fruitX && yPos == fruitY) {
        score++;
        fruitX = rand() % gameWidth;
        fruitY = rand() % gameHeight;
        snakeBody.push_front({ yPos, xPos });
    }
}


int main()
{
    initGameVariables();
    renderTheGame();

    while (!isGameOver) {
        userInput();
        updateGameState();
        renderTheGame();
      
    }

    std::cout << "Game over! Your final Score: " << score;

    return 0;
}