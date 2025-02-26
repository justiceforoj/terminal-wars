#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Ship.h"

#define GRID_SIZE 15

class Grid {
public:
    Grid();
    void placeShips();
    bool takeTurn(int x, int y);
    bool hasShipsLeft() const;
    char getCell(int x, int y) const;
    void setCell(int x, int y, char value);
    const std::vector<std::vector<char>>& getGrid() const;

private:
    std::vector<std::vector<char>> grid;
};

#endif
