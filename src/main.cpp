#include <iostream>
#include <ostream>
#include <string>
#include "fen.hpp"
#include "board.hpp"


int main () {
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    auto gameState = parceFENNotaion(fen);
    auto board = ChessBoard(gameState);
    auto moves = board.get_pseudo_legal_moves();
    std::cout << moves << std::endl;
    std::cout << std::endl;
    ChessBoard::print_empty_board();
    return 0;
}
