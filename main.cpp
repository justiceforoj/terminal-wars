#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#define GRID_SIZE 15

#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BOLD "\033[1m"
#define CLEAR_SCREEN "\033[H\033[J"

struct Ship {
    int length;
    char symbol;
};

std::vector<Ship> ships = {
    {5, 'C'}, // carrier
    {4, 'B'}, // battleship
    {3, 'D'}, // destroyer
    {3, 'S'}, // sub
    {2, 'P'}  // patrol boat
};

void clearScreen() {
    std::cout << CLEAR_SCREEN;
}

void moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void renderGrids(const std::vector<std::vector<char>>& playerGrid, const std::vector<std::vector<char>>& aiGrid, bool revealAI, const std::string& playerNotification, const std::string& aiNotification) {
    clearScreen();
    std::cout << BOLD << "  Player Board" << std::string(30, ' ') << "AI Board\n" << RESET;
    std::cout << "  A B C D E F G H I J K L M N O" << std::string(15, ' ') << "A B C D E F G H I J K L M N O\n";
    for (int i = 0; i < GRID_SIZE; i++) {
        std::cout << i + 1 << (i < 9 ? "  " : " ");
        for (char cell : playerGrid[i]) {
            if (cell == 'X') std::cout << RED << cell << RESET << " ";
            else if (cell == 'O') std::cout << BLUE << cell << RESET << " ";
            else std::cout << GREEN << cell << RESET << " ";
        }
        std::cout << std::string(10, ' ') << i + 1 << (i < 9 ? "  " : " ");
        for (char cell : aiGrid[i]) {
            if (!revealAI && (cell == 'C' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P')) std::cout << GREEN << "~" << RESET << " ";
            else if (cell == 'X') std::cout << RED << cell << RESET << " ";
            else if (cell == 'O') std::cout << BLUE << cell << RESET << " ";
            else std::cout << GREEN << cell << RESET << " ";
        }
        std::cout << "\n";
    }
    moveCursor(0, GRID_SIZE + 4);
    std::cout << BOLD << "Player: " << playerNotification << RESET << "\n";
    std::cout << BOLD << "AI: " << aiNotification << RESET << "\n";
}

void placeShips(std::vector<std::vector<char>>& grid) {
    srand(time(0));
    for (const Ship& ship : ships) {
        bool placed = false;
        while (!placed) {
            int x = rand() % GRID_SIZE;
            int y = rand() % GRID_SIZE;
            bool horizontal = rand() % 2;

            bool canPlace = true;
            for (int i = 0; i < ship.length; i++) {
                int nx = horizontal ? x + i : x;
                int ny = horizontal ? y : y + i;
                if (nx >= GRID_SIZE || ny >= GRID_SIZE || grid[ny][nx] != '~') {
                    canPlace = false;
                    break;
                }
            }

            if (canPlace) {
                for (int i = 0; i < ship.length; i++) {
                    int nx = horizontal ? x + i : x;
                    int ny = horizontal ? y : y + i;
                    grid[ny][nx] = ship.symbol;
                }
                placed = true;
            }
        }
    }
}

bool takeTurn(std::vector<std::vector<char>>& grid, int x, int y) {
    if (grid[y][x] != '~' && grid[y][x] != 'X' && grid[y][x] != 'O') {
        grid[y][x] = 'X'; // hit
        return true;
    }
    else {
        grid[y][x] = 'O'; // miss
        return false;
    }
}

void aiTurn(std::vector<std::vector<char>>& playerGrid, std::string& aiNotification) {
    int x, y;
    do {
        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
    } while (playerGrid[y][x] == 'X' || playerGrid[y][x] == 'O');

    bool hit = takeTurn(playerGrid, x, y);
    aiNotification = hit ? YELLOW "AI hit your ship!" RESET : "AI missed!";
}

bool hasShipsLeft(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == 'C' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') {
                return true;
            }
        }
    }
    return false; // no ships left
}

int main() {
    std::vector<std::vector<char>> playerGrid(GRID_SIZE, std::vector<char>(GRID_SIZE, '~'));
    std::vector<std::vector<char>> aiGrid(GRID_SIZE, std::vector<char>(GRID_SIZE, '~'));
    placeShips(playerGrid);
    placeShips(aiGrid);

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
            bool hit = takeTurn(aiGrid, x, y);
            playerNotification = hit ? YELLOW "You hit an enemy ship!" RESET : "You missed!";

            if (!hasShipsLeft(aiGrid)) {
                renderGrids(playerGrid, aiGrid, true, "You win! All AI ships destroyed!", "");
                break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            aiTurn(playerGrid, aiNotification);

            if (!hasShipsLeft(playerGrid)) {
                renderGrids(playerGrid, aiGrid, true, "Game Over! AI wins!", "");
                break;
            }
        }
        else {
            playerNotification = "Invalid input. Try again.";
        }
    }
    return 0;
}
