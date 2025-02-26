#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include "Grid.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BOLD "\033[1m"
#define CLEAR_SCREEN "\033[H\033[J"

void clearScreen();
void moveCursor(int x, int y);
void renderGrids(const Grid& playerGrid, const Grid& aiGrid, bool revealAI, const std::string& playerNotification, const std::string& aiNotification);

#endif
