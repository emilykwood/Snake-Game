// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h> 
#include <windows.h>
#include <cstdlib> 

//I was getting build errors before I added this in
void initGameVariables();
void renderTheGame();

// Declare the size of the game space
int gameHeight = 20;
int gameWidth = 80;
int score = 0;

int xPos, yPos; // position of the snake head
std::string fruit = "*";
int fruitX, fruitY; // holds the x and y position of the fruit the snake is trying to eat

bool isGameOver;


int main()
{
    initGameVariables();
    renderTheGame();
}

void initGameVariables() {
    isGameOver = false;
    fruitX = rand() % gameWidth;
    fruitY = rand() % gameHeight;
    xPos = gameWidth / 2;
    yPos = gameHeight / 2;
    score = 0;
}

void renderTheGame() {
    system("cls");// built-in method that clears the screen

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
            else if (j == fruitX && i == fruitY) {
                std::cout << fruit;
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < gameWidth; i++) {
        std::cout << "-";
    }

    std::cout << "\nScore: " + score;
}