#pragma once

#include <array>
#include <ostream>
#include <vector>
#include "figure.hpp"
#include "fen.hpp"

struct Move {
    uint from;
    uint to;
};

class ChessBoard {
private:
    std::array<Figure, 64> board_state;
    GameState game_state;
public:
    ChessBoard(GameState gs);
    Figure get(int row, int col) const { return board_state[row * 8 + col]; }
    Figure get(int index) const { return board_state[index]; }
    std::vector<Move> get_posible_moves();
    std::vector<Move> get_posible_moves(uint index);
};

std::ostream& operator<<(std::ostream& os, const ChessBoard& b);
std::ostream& operator<<(std::ostream& os, const Move& move);
std::ostream& operator<<(std::ostream& os, const std::vector<Move>& moves);
