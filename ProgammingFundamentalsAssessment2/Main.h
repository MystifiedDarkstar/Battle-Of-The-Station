#pragma once

#define arraySize(x) sizeof(x)/sizeof(x[0])

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <windows.h>

#include "Card.h"
#include "Player.h"
#include "Math.h"



void printGameHeader();
void startGame();
void gameLoop();
void printCommands();
void askPlayerInput();
void quitGame();
void startPlayerTurn();
void startAITurn();
void printTextToConsole(std::string input);