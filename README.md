# Snake Game in C++

## Overview

This is a simple implementation of the classic **Snake Game** written in C++. The player controls a snake, navigating through a grid, consuming fruit (represented by a `*`). Each time the snake eats a fruit, it grows longer, and the game gets progressively harder as the snake occupies more space. The game ends when the snake collides with the walls or itself.

## Features

- **Dynamic Snake Growth**: The snake grows longer each time it eats a fruit.
- **Basic Collision Detection**: The game ends if the snake hits the walls or itself.
- **Score Tracking**: The score increments with each fruit consumed.
- **Frame Rate Control**: Adjustable game speed using `Sleep()` for frame rate control.
- **Console-Based Graphics**: The game is rendered directly in the console using basic text characters.

## Game Controls

- **Up Arrow**: Move the snake up
- **Down Arrow**: Move the snake down
- **Left Arrow**: Move the snake left
- **Right Arrow**: Move the snake right

## How to Play

1. **Start the Game**: Run the program, and the game will render the grid, snake, and fruit in the console window.
2. **Move the Snake**: Use the arrow keys to control the snake. The snake will initially be stationary until the player presses a direction key.
3. **Eat Fruit**: Guide the snake to eat the fruit (represented by a `*`). Each time the snake eats fruit, it grows longer.
4. **Avoid Collisions**: The game ends if the snake collides with the walls or its own body.
5. **End of Game**: When the game is over, the final score will be displayed.

## Installation and Compilation

To compile and run this game on your local machine, follow these steps:

### Requirements

- A C++ compiler (like GCC or MSVC)
- Windows OS (due to usage of `<conio.h>` and `<windows.h>` libraries)
- Command line environment (CMD, PowerShell, etc.)

### Steps

1. **Clone the Repository**: Clone this repository to your local machine using:
   ```bash
   git clone https://github.com/yourusername/snake-game-cpp.git
