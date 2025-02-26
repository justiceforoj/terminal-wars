#include "Grid.h"
#include <cstdlib>
#include <ctime>

std::vector<Ship> ships = {
    {5, 'C'}, {4, 'B'}, {3, 'D'}, {3, 'S'}, {2, 'P'}
};

Grid::Grid() : grid(GRID_SIZE, std::vector<char>(GRID_SIZE, '~')) {}

void Grid::placeShips() {
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

bool Grid::takeTurn(int x, int y) {
    if (grid[y][x] != '~' && grid[y][x] != 'X' && grid[y][x] != 'O') {
        grid[y][x] = 'X';
        return true;
    }
    else {
        grid[y][x] = 'O';
        return false;
    }
}

bool Grid::hasShipsLeft() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == 'C' || cell == 'B' || cell == 'D' || cell == 'S' || cell == 'P') {
                return true;
            }
        }
    }
    return false;
}

char Grid::getCell(int x, int y) const {
    return grid[y][x];
}

void Grid::setCell(int x, int y, char value) {
    grid[y][x] = value;
}

const std::vector<std::vector<char>>& Grid::getGrid() const {
    return grid;
}
