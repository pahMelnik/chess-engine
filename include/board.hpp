#pragma once

#include <ostream>
#include <array>
#include <string>
#include "figure.hpp"

class ChessBoard {
private:
    std::array<Figure, 64> board;
public:
    ChessBoard();
    ChessBoard(const std::string& fen);
    const Figure& get(int row, int col) const;
    void loadFEN(const std::string& fen);
};

std::ostream& operator<<(std::ostream& os, const ChessBoard& b);
