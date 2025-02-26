#include "Grid.h"
#include "Utils.h"
#include <iostream>
#include <thread>
#include <chrono>

void aiTurn(Grid& playerGrid, std::string& aiNotification) {
    int x, y;
    do {
        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
    } while (playerGrid.getCell(x, y) == 'X' || playerGrid.getCell(x, y) == 'O');

    bool hit = playerGrid.takeTurn(x, y);
    aiNotification = hit ? YELLOW "AI hit your ship!" RESET : "AI missed!";
}

int main() {
    Grid playerGrid, aiGrid;
    playerGrid.placeShips();
    aiGrid.placeShips();

    std::string playerNotification = "Game Start!";
    std::string aiNotification = "";

    while (true) {
        renderGrids(playerGrid, aiGrid, false, playerNotification, aiNotification);

        char col;
        int row;
        std::cout << "Enter target (e.g., A1): ";
        std::cin >> col >> row;

        int x = col - 'A';
        int y = row - 1;

        if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
            bool hit = aiGrid.takeTurn(x, y);
            playerNotification = hit ? YELLOW "You hit an enemy ship!" RESET : "You missed!";

            if (!aiGrid.hasShipsLeft()) break;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            aiTurn(playerGrid, aiNotification);

            if (!playerGrid.hasShipsLeft()) break;
        }
        else {
            playerNotification = "Invalid input. Try again.";
        }
    }

    return 0;
}
