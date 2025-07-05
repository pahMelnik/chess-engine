#include <iostream>
#include <string>
#include "fen.hpp"
#include "figure.hpp"
#include "board.hpp"


int main () {
    // ChessBoard board;
    // std::cout << board;
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    auto fn = FenNotation(fen);
    std::cout << fn;
    return 0;
}
