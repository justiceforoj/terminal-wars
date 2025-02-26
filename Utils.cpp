#include "Utils.h"

void clearScreen() {
    std::cout << CLEAR_SCREEN;
}

void moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void renderGrids(const Grid& playerGrid, const Grid& aiGrid, bool revealAI, const std::string& playerNotification, const std::string& aiNotification) {
    clearScreen();
    std::cout << BOLD << "  Player Board" << std::string(30, ' ') << "AI Board\n" << RESET;
    std::cout << "  A B C D E F G H I J K L M N O" << std::string(15, ' ') << "A B C D E F G H I J K L M N O\n";

    for (int i = 0; i < GRID_SIZE; i++) {
        std::cout << i + 1 << (i < 9 ? "  " : " ");
        for (int j = 0; j < GRID_SIZE; j++) {
            char cell = playerGrid.getCell(j, i);
            if (cell == 'X') std::cout << RED << cell << RESET << " ";
            else if (cell == 'O') std::cout << BLUE << cell << RESET << " ";
            else std::cout << GREEN << cell << RESET << " ";
        }
        std::cout << std::string(10, ' ') << i + 1 << (i < 9 ? "  " : " ");
        for (int j = 0; j < GRID_SIZE; j++) {
            char cell = aiGrid.getCell(j, i);
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
